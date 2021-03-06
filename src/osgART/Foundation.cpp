/* -*-c++-*- 
 * 
 * osgART - Augmented Reality ToolKit for OpenSceneGraph
 * 
 * Copyright (C) 2005-2009 Human Interface Technology Laboratory New Zealand
 * Copyright (C) 2010-2014 Raphael Grasset, Julian Looser, Hartmut Seichter
 *
 * This library is open source and may be redistributed and/or modified under
 * the terms of the OpenSceneGraph Public License (OSGPL) version 0.0 or
 * (at your option) any later version.  The full license is in LICENSE file
 * included with this distribution, and on the osgart.org website.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * OpenSceneGraph Public License for more details.
*/

// local include
#include "osgART/Foundation"
#include "osgART/PluginManager"

// OpenThreads include

// OSG include
#include <osg/Version>
#include <osg/Notify>

#include <osgDB/Registry>
#include <osgDB/FileUtils>


#include "osgART/CoreConfiguration"


namespace osgART {

	class Initializer
	{
	public:

		Initializer()
		{

            OSG_NOTICE << "osgART::Initializer()" << std::endl;


		}

		~Initializer()
		{
			// Delete the Plugin Manager
			osgART::PluginManager::instance(true);
		}

	};

}

/* global initializer */
static osgART::Initializer g_Initializer;
osgART::Initializer* p_gInitializer = &g_Initializer;


