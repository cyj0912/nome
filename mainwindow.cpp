/**
 * @author Andy Wang, UC Berkeley.
 * Copyright 2016 reserve.
 * UC Berkeley, Slide_2016 project.
 * Advised by Prof. Sequin H. Carlos.
 */

#include "mainwindow.h"

MainWindow::MainWindow()
{
    createActions();
    createMenus();
    //createControlPanel(canvas);
    //setCentralWidget(controls);
}

void MainWindow::open()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Import Input File"), "/", tr("Geometry Files (*.nom *.sif *.anom)"));
    if(fileName == "")
    {
        return;
    }
    createCanvas(fileName);
}

void MainWindow::save()
{
    QString fileName = QFileDialog::getSaveFileName(this,
         tr("Save Output File"), "/", tr("Output Files (*.stl *.nom *.anom)"));
    if(fileName == "")
    {
        return;
    }
    else if(canvas == NULL)
    {
        cout<<"Error: No work to be saved!"<<endl;
        return;
    }
    else if(fileName.right(3).toLower() == "stl")
    {
        canvas -> saveMesh(fileName.toStdString());
    }
    else if(fileName.right(4).toLower() == "anom")
    {
        save_current_status_anom(fileName.toStdString());
    }
    else
    {
        save_current_status_nome(fileName.toStdString());
    }
}

void MainWindow::close()
{
    if(canvas != NULL) {
        canvas -> hierarchical_scene_transformed.clearAndDelete();
        canvas -> master_mesh.clearAndDelete();
        //canvas -> temp_mesh.clearAndDelete();
        //canvas -> consolidate_mesh.clearAndDelete();
        //canvas -> merged_mesh.clearAndDelete();
        //canvas -> subdiv_mesh.clearAndDelete();
        //canvas -> offset_mesh.clearAndDelete();
        canvas -> close();
        scene.clearAndDelete();
        append_scene.clearAndDelete();
        nomeParser = NULL;
        delete(canvas);
        canvas = NULL;
        controls -> close();
        delete(controls);
        controls = NULL;
        for(SliderPanel*& panel: slider_panels)
        {
            panel->close();
            delete(panel);
            panel = NULL;
        }
        slider_panels.clear();
        banklines.clear();
        colorlines.clear();
        geometrylines.clear();
        postProcessingLines.clear();
        banks.clear();
        params.clear();
    }
}

void MainWindow::quit()
{
    exit(1);
}

void MainWindow::createActions()
{
    openAct = new QAction(tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open a SIF or NOME file"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

    saveAct = new QAction(tr("&Save..."), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save your work as a NOME or STL file"));
    connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

    closeAct = new QAction(tr("&Close..."), this);
    closeAct->setShortcuts(QKeySequence::Close);
    closeAct->setStatusTip(tr("Close the file and canvas"));
    connect(closeAct, SIGNAL(triggered()), this, SLOT(close()));

    quitAct = new QAction(tr("&Quit..."), this);
    quitAct->setShortcuts(QKeySequence::Quit);
    quitAct->setStatusTip(tr("Open an existing file"));
    connect(quitAct, SIGNAL(triggered()), this, SLOT(quit()));
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(closeAct);
    fileMenu->addAction(quitAct);
}
void MainWindow::createCanvas(QString name)
{
    if(name.right(3).toLower() == "sif")
    {
        canvas = new SlideGLWidget(name.toStdString());
        canvas -> move(0, 50);
        canvas -> show();
        createControlPanel(canvas);
    }
    else if(name.right(4).toLower() == "anom")
    {
        if(canvas == NULL)
        {
            cout<<"Warning: you need an existing working slf file to open this file.\n";
            return;
        }
        else
        {
            canvas -> group_from_consolidate_mesh = &append_scene;
            nomeParser->appendWithANOM(params, append_scene, canvas, name.toStdString());
        }
    }
    else if (name.right(3).toLower() == "nom")
    {
        slider_panels.clear();
        banklines.clear();
        colorlines.clear();
        geometrylines.clear();
        postProcessingLines.clear();
        banks.clear();
        params.clear();
        //=======

        int error = 0;
        error = nomeParser->makeWithNome(banks, params, scene, name.toStdString(),
                                 colorlines, banklines, geometrylines, postProcessingLines);

        if (error == 1){
            return;
        }

        canvas = new SlideGLWidget(scene);
        canvas -> group_from_consolidate_mesh = &append_scene;
        nomeParser->postProcessingWithNome(params, postProcessingLines, canvas, append_scene, name.toStdString());
        createSliderPanel(canvas);
        canvas -> move(0, 50);
        canvas -> show();
        createControlPanel(canvas);
    }
    else
    {
        cout<<"File type not supported!";
    }

}

void MainWindow::createSliderPanel(SlideGLWidget * canvas)
{
    for(size_t i = 0; i < banks.size(); i++)
    {
        SliderPanel *newPanel = new SliderPanel(&banks[i], canvas);
        newPanel -> show();
        newPanel -> move(10, 10);
        slider_panels.push_back(newPanel);
    }
}

void MainWindow::createControlPanel(SlideGLWidget * canvas)
{
    controls = new ControlPanel(canvas);
    controls -> move(900, 50);
    controls -> show();
}

void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    menu.exec(event->globalPos());
}

void MainWindow::save_current_status_anom(string out_put_file)
{
    ofstream file(out_put_file);
    if (!file.is_open())
    {
        cout <<"Error: COULD NOT OPEN THE FILE.\n";
    }
    else
    {
        file<<"savedparameter\n";
        for(ParameterBank& bank : banks)
        {
            for(Parameter*& p : bank.parameters)
            {
                file<<"    "<<(p->name).toStdString()<<" "<<to_string(p->value)<<"\n";
            }
        }
        file<<"endsavedparameter\n";
        if(!(canvas->consolidate_mesh).isEmpty())
        {
            file<<"\n";
            file<<"consolidate\n";
            for(Face*& face: (canvas->consolidate_mesh).faceList)
            {
                file<<"    consolidateface\n";
                Edge * firstEdge = face -> oneEdge;
                Edge * currEdge = firstEdge;
                Edge * nextEdge;
                Vertex * tempv;
                do {
                    if(face == currEdge -> fa) {
                        tempv = currEdge -> vb;
                        nextEdge = currEdge -> nextVbFa;
                    } else {
                        if(currEdge -> mobius) {
                            tempv = currEdge -> vb;
                            nextEdge = currEdge -> nextVbFb;
                        } else {
                            tempv = currEdge -> va;
                            nextEdge = currEdge -> nextVaFb;
                        }
                    }
                    file<<"        vertex "<<tempv->name<<" endvertex\n";
                    currEdge = nextEdge;
                } while (currEdge != firstEdge);
                file<<"    endconsolidateface\n";
            }
            file<<"endconsolidate\n";
        }
    }
}

void MainWindow::save_current_status_nome(string out_put_file)
{
    ofstream file(out_put_file);
    if (!file.is_open())
    {
        cout <<"Error: COULD NOT OPEN THE FILE.\n";
    }
    else
    {
        string bankname = "";
        if(colorlines.size() > 0)
        {
            file<<"#### Some Surface colors #####\n";
            for(string& line : colorlines)
            {
                file<<line<<'\n';
            }
            file<<"\n";
        }
        for(string& line : banklines)
        {
            istringstream iss(line);
            vector<string> tokens;
            copy(istream_iterator<string>(iss),
                 istream_iterator<string>(),
                 back_inserter(tokens));
            //file << line <<'\n';
            if(tokens[0] == "bank")
            {
                bankname = tokens[1];
            }
            if(tokens[0] == "set")
            {
                file << "    ";
                for(int i = 0; i < tokens.size(); i++)
                {
                    if(i == 2)
                    {
                        file << params[bankname + "_" + tokens[1]].value;
                    }
                    else
                    {
                        file << tokens[i];
                    }
                    file<<'\t'<<'\t';
                }
                file << '\n';
            }
            else
            {
                file << line <<'\n';
            }
        }
        for(string& line : geometrylines)
        {
            file<<line<<'\n';
        }
    }
    if(!(canvas->consolidate_mesh).isEmpty() || (canvas -> deletedFaces).size() > 0)
    {
        file<<"\n##### The following is the saved work of last time. #####\n"<<endl;
    }
    if(!(canvas->consolidate_mesh).isEmpty())
    {
        file<<"##### The added faces. #####\n";
        file<<"mesh consolidatedmesh\n";
        int counter = 0;
        for(Face*& face: (canvas->consolidate_mesh).faceList)
        {
            file<<"    face";
            file<<" consolidatedface"<<counter++<<" (";
            Edge * firstEdge = face -> oneEdge;
            Edge * currEdge = firstEdge;
            Edge * nextEdge;
            Vertex * tempv;
            do {
                if(face == currEdge -> fa) {
                    tempv = currEdge -> vb;
                    nextEdge = currEdge -> nextVbFa;
                } else {
                    if(currEdge -> mobius) {
                        tempv = currEdge -> vb;
                        nextEdge = currEdge -> nextVbFb;
                    } else {
                        tempv = currEdge -> va;
                        nextEdge = currEdge -> nextVaFb;
                    }
                }
                file<<tempv->source_vertex->name<<" ";
                currEdge = nextEdge;
            } while (currEdge != firstEdge);
            file<<") endface\n";
        }
        file<<"endmesh\n";

    }
    if((canvas -> deletedFaces).size() > 0)
    {
        file<<"\n##### The deleted faces #####\n";
        file<<"delete\n";
        for(string deletedFace : (canvas->deletedFaces))
        {
            file<<"    face "<<deletedFace<<" endface\n";
        }
        file<<"enddelete\n";
    }
    if(!(canvas->consolidate_mesh).isEmpty())
    {
        file<<"\n####Create an instance of the consolidated mesh here.####\n"<<endl;
        file<<"instance cm1 consolidatedmesh endinstance\n";
    }
}
