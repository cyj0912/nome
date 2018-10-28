#include "mainwindow.h"

#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>

CMainWindow::CMainWindow(QWidget* parent) : QMainWindow(parent)
{
	SetupUi();
}

CMainWindow::~CMainWindow()
{
}

void CMainWindow::SetupUi()
{
	auto* MainWindow = this;

	//Copied from designer
	if (MainWindow->objectName().isEmpty())
		MainWindow->setObjectName(QStringLiteral("MainWindow"));
	MainWindow->resize(800, 600);
	actionNew = new QAction(MainWindow);
	actionNew->setObjectName(QStringLiteral("actionNew"));
	actionOpen = new QAction(MainWindow);
	actionOpen->setObjectName(QStringLiteral("actionOpen"));
	actionSave = new QAction(MainWindow);
	actionSave->setObjectName(QStringLiteral("actionSave"));
	actionSave_As = new QAction(MainWindow);
	actionSave_As->setObjectName(QStringLiteral("actionSave_As"));
	actionClose = new QAction(MainWindow);
	actionClose->setObjectName(QStringLiteral("actionClose"));
	actionQUit = new QAction(MainWindow);
	actionQUit->setObjectName(QStringLiteral("actionQUit"));
	actionAbout = new QAction(MainWindow);
	actionAbout->setObjectName(QStringLiteral("actionAbout"));
	actionAbout_Qt = new QAction(MainWindow);
	actionAbout_Qt->setObjectName(QStringLiteral("actionAbout_Qt"));
	actionQuit = new QAction(MainWindow);
	actionQuit->setObjectName(QStringLiteral("actionQuit"));
	centralwidget = new QWidget(MainWindow);
	centralwidget->setObjectName(QStringLiteral("centralwidget"));
	horizontalLayout = new QHBoxLayout(centralwidget);
	horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
	MainWindow->setCentralWidget(centralwidget);
	menubar = new QMenuBar(MainWindow);
	menubar->setObjectName(QStringLiteral("menubar"));
	menubar->setGeometry(QRect(0, 0, 800, 26));
	menuFile = new QMenu(menubar);
	menuFile->setObjectName(QStringLiteral("menuFile"));
	menuHelp = new QMenu(menubar);
	menuHelp->setObjectName(QStringLiteral("menuHelp"));
	MainWindow->setMenuBar(menubar);
	statusbar = new QStatusBar(MainWindow);
	statusbar->setObjectName(QStringLiteral("statusbar"));
	MainWindow->setStatusBar(statusbar);

	menubar->addAction(menuFile->menuAction());
	menubar->addAction(menuHelp->menuAction());
	menuFile->addAction(actionNew);
	menuFile->addAction(actionOpen);
	menuFile->addSeparator();
	menuFile->addAction(actionSave);
	menuFile->addAction(actionSave_As);
	menuFile->addSeparator();
	menuFile->addAction(actionClose);
	menuFile->addSeparator();
	menuFile->addAction(actionQuit);
	menuHelp->addAction(actionAbout);
	menuHelp->addAction(actionAbout_Qt);

	QMetaObject::connectSlotsByName(MainWindow);
}

#if 0
/**
 * @author Andy Wang, UC Berkeley.
 * Copyright 2016 reserve.
 * UC Berkeley, Slide_2016 project.
 * Advised by Prof. Sequin H. Carlos.
 */

#include "mainwindow.h"
#include "newNOME/SliderNew.h"
#include "newNOME/SliderSubdivisionNew.h"
#include "newNOME/SliderOffsetNew.h"

MainWindow::MainWindow()
{
    createActions();
    createMenus();
}

void MainWindow::recreateSliders()
{
	for (auto* widget : presentSliderWindows)
		delete widget;
	presentSliderWindows.clear();
	drawSliders(canvas, currSession);
	drawSubdivisionSliders(canvas, currSession);
	drawOffsetSliders(canvas, currSession);
}

void MainWindow::open()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Import Input File"), "/", tr("Geometry Files (*.stl *.nom *.obj)"));
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
        currSession->SaveSessionStl(fileName.toStdString());
    }
    else if(fileName.right(4).toLower() == "anom")
    {
        save_current_status_anom(fileName.toStdString());
    }
    else
    {
        currSession->SaveSessionNom(fileName.toStdString());
        //save_current_status_nome(fileName.toStdString());
    }
}

void MainWindow::close()
{
    if(canvas != NULL) {
        canvas -> hierarchical_scene_transformed.clearAndDelete();
        canvas -> master_mesh.clearAndDelete();
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
        postProcessingLinesString.clear();
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
        Session* currSession = new Session();
        createControlPanel(canvas, currSession);
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
            //nomeParser->appendWithANOM(params, append_scene, canvas, name.toStdString());
        }
    }
    else if ((name.right(3).toLower() == "stl") || (name.right(3).toLower() == "nom") || (name.right(3).toLower() == "obj"))
    {
        slider_panels.clear();
        banklines.clear();
        colorlines.clear();
        geometrylines.clear();
        postProcessingLines.clear();
        postProcessingLinesString.clear();
        banks.clear();
        params.clear();
        //=======
        unordered_map<string, Vertex*> global_vertices;
        unordered_map<string, Face*> global_faces;
        int error = 0;

        currSession = nomeParser->makeWithNome(banks, params, scene, name.toStdString(),
                                 colorlines, banklines, geometrylines, postProcessingLines, postProcessingLinesString, global_vertices, global_faces);

        if (error == 1){
            return;
        }

        canvas = new SlideGLWidget(scene, currSession);

        if (error == 1){
            return;
        }

        drawSliders(canvas, currSession);
        drawSubdivisionSliders(canvas, currSession);
        drawOffsetSliders(canvas, currSession);

        canvas -> move(0, 50);
        canvas -> show();
        createControlPanel(canvas, currSession);
        canvas -> updateGL();

    }
    else
    {
        cout<<"File type not supported!";
    }

}

void MainWindow::drawSliders(SlideGLWidget * canvas, Session *currSession)
{
    for(auto b : currSession->banks) {
        QWidget *window = new QWidget;
        window->resize(400,0);
        QVBoxLayout* layout = new QVBoxLayout(window);
        QLabel* label = new QLabel(b->name.c_str());
        layout->addWidget(label);
        for(auto s : b->sets) {
            layout -> addLayout(new SliderNew(s, canvas));
        }
        window->setLayout(layout);
        window->show();

		presentSliderWindows.push_back(window);
    }
}

void MainWindow::drawSubdivisionSliders(SlideGLWidget * canvas, Session *currSession)
{
    QWidget *window = new QWidget;
    window->resize(400,0);
    QVBoxLayout* layout = new QVBoxLayout(window);
    QLabel* label = new QLabel("SUBDIVISION");
    layout->addWidget(label);
    for(SubdivisionNew* sd : currSession->subdivisions) {
        layout -> addLayout(new SliderSubdivisionNew(sd, canvas));
        window -> setLayout(layout);
    }
    window->show();
	presentSliderWindows.push_back(window);
}

void MainWindow::drawOffsetSliders(SlideGLWidget * canvas, Session *currSession)
{
    QWidget *window = new QWidget;
    window->resize(400,0);
    QVBoxLayout* layout = new QVBoxLayout(window);
    QLabel* label = new QLabel("OFFSET");
    layout->addWidget(label);
    for(OffsetNew* sd : currSession->offsets) {
        layout -> addLayout(new SliderOffsetNew(sd, canvas));
        window -> setLayout(layout);
    }
    window->show();
	presentSliderWindows.push_back(window);
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

void MainWindow::createControlPanel(SlideGLWidget * canvas, Session * currSession)
{
    controls = new ControlPanel(this, canvas, currSession);
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
                        file << params[bankname + "." + tokens[1]].value;
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

        for(string& line : postProcessingLinesString)
        {
            file<< line <<'\n';
        }
    }

    std::string consolidatedMeshName;
    if(!(canvas->consolidate_mesh).isEmpty() || (canvas -> deletedFaces).size() > 0)
    {
        file<<"\n##### The following is the saved work of last time. #####\n"<<endl;
    }
    if(!(canvas->consolidate_mesh).isEmpty())
    {
        file<<"##### The added faces. #####\n";

        int meshNumber = 0;
        bool foundAvailableMeshName = false;


        while (!foundAvailableMeshName){
            consolidatedMeshName = "consolidatedmesh";
            consolidatedMeshName += std::to_string(meshNumber);

            if ((canvas -> group_from_consolidate_mesh)->myMeshes.size() == 0){
                foundAvailableMeshName = true;
                break;
            }

            if (canvas->meshes.find(consolidatedMeshName) == canvas->meshes.end()){
                foundAvailableMeshName = true;
                break;
            }

            meshNumber += 1;
        }
        file<<"mesh " + consolidatedMeshName + "\n";
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

        int instanceNumber = 0;
        bool foundAvailableInstanceName = false;
        std::string instanceName;
        while (!foundAvailableInstanceName){
            instanceName = "cm";
            instanceName += std::to_string(instanceNumber);

            int numberInstances = (canvas -> group_from_consolidate_mesh)->myMeshes.size();
            int i = 0;

            if ((canvas -> group_from_consolidate_mesh)->myMeshes.size() == 0){
                foundAvailableInstanceName = true;
                break;
            }

            foundAvailableInstanceName = true;
            while (i < numberInstances){
                if (instanceName.compare((canvas -> group_from_consolidate_mesh)->myMeshes[i].name) == 0){
                    foundAvailableInstanceName = false;
                }
                i += 1;
            }
            instanceNumber += 1;
        }
        file<<"instance " + instanceName + " " + consolidatedMeshName + " endinstance\n";
    }
}
#endif
