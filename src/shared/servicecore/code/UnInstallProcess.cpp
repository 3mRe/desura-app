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

#include "Common.h"
#include "UnInstallProcess.h"
#include "McfInit.h"
#include "InstallScriptRunTime.h"
#include "mcfcore/MCFMain.h"

UninstallProcess::UninstallProcess(const char* mcfpath, const char* inspath, const char* installScript)
	: Thread::BaseThread("UninstallProcess Thread")
	, m_szMCFPath(mcfpath)
	, m_szIPath(inspath)
	, m_szInstallScript(installScript)
{
}

UninstallProcess::~UninstallProcess()
{
	stop();
}

void UninstallProcess::run()
{
	gcTrace("");

	if (m_szIPath == "" || m_szMCFPath == "")
	{
		gcException errPathNull(ERR_BADPATH, gcString("One of the paths for uninstall was nullptr [IP: {0} MCF: {1}].", m_szIPath, m_szMCFPath));
		onErrorEvent(errPathNull);
		return;
	}

	McfHandle mcfHandle;
	mcfHandle->getErrorEvent() += delegate(&onErrorEvent);
	mcfHandle->getProgEvent() += delegate(this, &UninstallProcess::onProgress);

	InstallScriptRunTime isrt(m_szInstallScript.c_str(), m_szIPath.c_str());

	try
	{
		AutoScopeLockedMemberVar<MCFCore::MCFI> asmv1(m_pMcfHandle, m_McfLock, mcfHandle);

		mcfHandle->setFile(m_szMCFPath.c_str());
		mcfHandle->parseMCF();

		isrt.run("PreUninstall");
		mcfHandle->removeFiles(m_szIPath.c_str());
		isrt.run("PostUninstall");
	}
	catch (gcException &except)
	{
		onErrorEvent(except);
	}

	onCompleteEvent();
}

void UninstallProcess::onStop()
{
	std::lock_guard<std::mutex> gaurd(m_McfLock);

	if (m_pMcfHandle)
		m_pMcfHandle->stop();
}

void UninstallProcess::onProgress(MCFCore::Misc::ProgressInfo& p)
{
	uint64 val = p.toInt64();

	if (val == m_uiLastProg)
		return;

	onProgressEvent(val);
	m_uiLastProg = val;
}
