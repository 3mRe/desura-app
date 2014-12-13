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

#ifndef DESURA_TABBUTTON_H
#define DESURA_TABBUTTON_H
#ifdef _WIN32
#pragma once
#endif

#include <wx/control.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/sizer.h>
#include <wx/panel.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class tabButton
///////////////////////////////////////////////////////////////////////////////
class tabButton : public wxPanel
{
public:
	tabButton( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 100,40 ), long style = wxNO_BORDER|wxTAB_TRAVERSAL );
	~tabButton();

	void setText(const char* text);
	void setSelected(bool state);

	void setPageId(int32 id){m_iId = id;}
	int32 getPageId(){return m_iId;}

protected:

	wxStaticText* m_labTitle;

	// Virtual event handlers, overide them in your derived class
	virtual void onMouseOver( wxMouseEvent& event );
	virtual void onMouseOut( wxMouseEvent& event );
	virtual void onMouseEvent( wxMouseEvent& event );
	virtual void onMouseDown( wxMouseEvent& event );

	void updateMouse(wxMouseEvent& event);

private:
	int32 m_iId;
	bool m_bSelected;

DECLARE_EVENT_TABLE()

};


#endif //DESURA_TABBUTTON_H
