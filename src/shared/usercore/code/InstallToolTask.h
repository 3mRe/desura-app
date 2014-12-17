/*
Copyright (C) 2011 Mark Chandler (Desura Net Pty Ltd)
Copyright (C) 2014 Bad Juju Games, Inc.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software Foundation,
Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA.

Contact us at legal@badjuju.com.
*/

#ifndef DESURA_INSTALLTOOLTASK_H
#define DESURA_INSTALLTOOLTASK_H
#ifdef _WIN32
#pragma once
#endif

#include "BaseItemTask.h"
#include "usercore/ItemHelpersI.h"
#include "ToolManager.h"

#include "util_thread/BaseThread.h"

namespace UserCore
{
	namespace ItemTask
	{
		class InstallToolTask : public UserCore::ItemTask::BaseItemTask
		{
		public:
			InstallToolTask(gcRefPtr<UserCore::Item::ItemHandleI> handle, bool launch);
			virtual ~InstallToolTask();

		protected:
			void doRun();

			virtual void onPause();
			virtual void onUnpause();
			virtual void onStop();

			void onIPCStart();
			void onINStart(DesuraId &id);
			void onINProgress(UserCore::Misc::ToolProgress &p);
			void onINError(gcException &e);
			void onINComplete();

			void onComplete();

		private:
			bool m_bInError;
			bool m_bLaunch;

			uint32 m_ToolTTID;
			::Thread::WaitCondition m_WaitCond;
		};
	}
}


#endif //DESURA_INSTALLTOOLTASK_H
