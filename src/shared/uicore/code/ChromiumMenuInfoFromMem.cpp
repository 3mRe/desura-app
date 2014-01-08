/*
Desura is the leading indie game distribution platform
Copyright (C) 2011 Mark Chandler (Desura Net Pty Ltd)

$LicenseInfo:firstyear=2014&license=lgpl$
Copyright (C) 2014, Linden Research, Inc.

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation;
version 2.1 of the License only.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, see <http://www.gnu.org/licenses/>
or write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

Linden Research, Inc., 945 Battery Street, San Francisco, CA  94111  USA
$/LicenseInfo$
*/

#include "Common.h"
#include "ChromiumMenuInfoFromMem.h"

class MenuItem : public ChromiumDLL::ChromiumMenuItemI
{
public:
	virtual int getAction()
	{
		return m_Action;
	}

	virtual int getType()
	{
		return m_Type;
	}

	virtual const char* getLabel()
	{
		return m_szLabel.c_str();
	}

	virtual bool isEnabled()
	{
		return m_bEnabled;
	}

	virtual bool isChecked()
	{
		return m_bChecked;
	}

	int m_Action;
	int m_Type;
	gcString m_szLabel;

	bool m_bEnabled;
	bool m_bChecked;
};


ChromiumMenuInfoFromMem::ChromiumMenuInfoFromMem(const char* buff, uint32 size)
{
	auto readString = [&buff](gcString &str)
	{
		char tempBuff[255];

		unsigned char temp;
		CopyMemory((void*)&temp, buff, 1);
		buff++;

		CopyMemory((void*)tempBuff, buff, temp);
		buff+=temp;

		str.assign(tempBuff, temp);
	};

	CopyMemory((void*)&m_Type, buff, 4);
	buff+=4;

	CopyMemory((void*)&m_Edit, buff, 4);
	buff+=4;

	CopyMemory((void*)&m_X, buff, 4);
	buff+=4;

	CopyMemory((void*)&m_Y, buff, 4);
	buff+=4;

	readString(m_szLinkUrl);
	readString(m_szImgUrl);
	readString(m_szPageUrl);
	readString(m_szFrameUrl);
	readString(m_szSelectionText);
	readString(m_szMisSpelledWord);
	readString(m_szSecurityInfo);

	size_t num;
	CopyMemory((void*)&num, buff, 4);
	buff+=4;

	for (size_t x=0; x<num; x++)
	{
		MenuItem* mi = new MenuItem();

		CopyMemory((void*)&(mi->m_Action), buff, 4);
		buff+=4;

		CopyMemory((void*)&(mi->m_Type), buff, 4);
		buff+=4;

		readString(mi->m_szLabel);


		char t;
		CopyMemory((void*)&t, buff, 1);
		buff++;

		mi->m_bEnabled = t?true:false;

		CopyMemory((void*)&t, buff, 1);
		buff++;

		mi->m_bChecked = t?true:false;
	}

	CopyMemory((void*)&m_Hwnd, buff, 4);
	buff+=4;
}

ChromiumMenuInfoFromMem::~ChromiumMenuInfoFromMem()
{
	safe_delete(m_vMenuItems);
}

ChromiumDLL::ChromiumMenuInfoI::TypeFlags ChromiumMenuInfoFromMem::getTypeFlags()
{
	return m_Type;
}

ChromiumDLL::ChromiumMenuInfoI::EditFlags ChromiumMenuInfoFromMem::getEditFlags()
{
	return m_Edit;
}

void ChromiumMenuInfoFromMem::getMousePos(int* x, int* y)
{
	*x = m_X;
	*y = m_Y;
}

const char* ChromiumMenuInfoFromMem::getLinkUrl()
{
	return m_szLinkUrl.c_str();
}

const char* ChromiumMenuInfoFromMem::getImageUrl()
{
	return m_szImgUrl.c_str();
}

const char* ChromiumMenuInfoFromMem::getPageUrl()
{
	return m_szPageUrl.c_str();
}

const char* ChromiumMenuInfoFromMem::getFrameUrl()
{
	return m_szFrameUrl.c_str();
}

const char* ChromiumMenuInfoFromMem::getSelectionText()
{
	return m_szSelectionText.c_str();
}

const char* ChromiumMenuInfoFromMem::getMisSpelledWord()
{
	return m_szMisSpelledWord.c_str();
}

const char* ChromiumMenuInfoFromMem::getSecurityInfo()
{
	return m_szSecurityInfo.c_str();
}

int ChromiumMenuInfoFromMem::getCustomCount()
{
	return m_vMenuItems.size();
}

ChromiumDLL::ChromiumMenuItemI* ChromiumMenuInfoFromMem::getCustomItem(size_t index)
{
	return m_vMenuItems[index];
}

int* ChromiumMenuInfoFromMem::getHWND()
{
	return m_Hwnd;
}
