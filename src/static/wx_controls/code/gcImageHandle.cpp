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
#include "gcImageHandle.h"
#include "gcManagers.h"

gcImageHandle::gcImageHandle()
{
	m_pMang = nullptr;
	m_pImg = nullptr;
	m_uiHash = 0;
}

gcImageHandle::gcImageHandle(gcImage* img, uint32 hash, gcThemeManagerI* mng)
{
	m_pMang = mng;
	m_pImg = img;
	m_uiHash = hash;
}

gcImageHandle::gcImageHandle(const gcImageHandle& h)
{
	m_pMang = h.m_pMang;
	m_pImg = h.m_pImg;
	m_uiHash = h.m_uiHash;
	m_pMang->newImgHandle(m_uiHash);
}

gcImageHandle::~gcImageHandle()
{
	if (m_pMang)
		m_pMang->desposeImgHandle(m_uiHash);
}

gcImageHandle& gcImageHandle::operator= (const gcImageHandle& h)
{
	m_pMang = h.m_pMang;
	m_pImg = h.m_pImg;
	m_uiHash = h.m_uiHash;

	if (m_pMang)
		m_pMang->newImgHandle(m_uiHash);

	return *this;
}

gcImage* gcImageHandle::operator->()
{
	return m_pImg;
}

gcImage* gcImageHandle::getImg()
{
	return m_pImg;
}
