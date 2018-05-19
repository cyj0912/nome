//
//  Group.cpp
//  model
//
//  Created by L on 22/09/2017.
//  Copyright © 2017 L. All rights reserved.
//

#include <stdio.h>
#include "GroupNew.h"

GroupNew* createGroup(std::list<InstanceNew*> li0)
{
    GroupNew* g0 = new GroupNew();
    g0->instances = li0;
    return g0;
}

bool GroupNew::setName(std::string n)
{
    if(n.find(".") != std::string::npos && n.find(":") != std::string::npos)
        return false;
    name = n;
    return updateNames();
}


bool GroupNew::updateNames()
{
    for (InstanceNew* m0 : instances)
    {
        m0->setPrefix(getFullName());
        m0->updateNames();
    }
    return true;
}

bool GroupNew::draw()
{
    for(InstanceNew* i0 : instances) {
      i0->draw();
    }

    return true;
}
