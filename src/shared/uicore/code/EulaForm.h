/*
Desura is the leading indie game distribution platform
Copyright (C) 2011 Mark Chandler (Desura Net Pty Ltd)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>
*/

#ifndef DESURA_EULAFORM_H
#define DESURA_EULAFORM_H
#ifdef _WIN32
#pragma once
#endif

#include "wx_controls/gcControls.h"
#include "wx/wx.h"
#include "gcMiscWebControl.h"

namespace UserCore
{
	class ItemManagerI;
}

class EULAForm : public gcFrame 
{
public:
	EULAForm(wxWindow* parent, UserCore::ItemManagerI* pItemManager = nullptr);
	~EULAForm();

	bool setInfo(DesuraId id);
	DesuraId getItemId(){return m_uiInternId;}

protected:
	wxStaticText* m_labInfo;
	gcMiscWebControl* m_ieBrowser;

	gcButton* m_butAgree;
	gcButton* nm_butCancel;

	wxBoxSizer *m_BrowserSizer;

	void onButtonPressed(wxCommandEvent& event);
	void onFormClose( wxCloseEvent& event );

	void onNewUrl(newURL_s& info);
	void onPageLoad();

private:
	DesuraId m_uiInternId;
	bool m_bLoadingProperPage;

	UserCore::ItemManagerI* m_pItemManager = nullptr;
};

#endif //DESURA_EULAFORM_H
