/*
* This file is part of wxSmith plugin for Code::Blocks Studio
* Copyright (C) 2006-2007  Bartlomiej Swiecki
*
* wxSmith is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 3 of the License, or
* (at your option) any later version.
*
* wxSmith is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with wxSmith. If not, see <http://www.gnu.org/licenses/>.
*
* $Revision: 8148 $
* $Id: wxslistbook.h 8148 2012-07-19 19:50:28Z mortenmacfly $
* $HeadURL: https://svn.code.sf.net/p/codeblocks/code/trunk/src/plugins/contrib/wxSmith/wxwidgets/defitems/wxslistbook.h $
*/

#ifndef WXSLISTBOOK_H
#define WXSLISTBOOK_H

#include "../wxscontainer.h"

/** \brief Listbook container */
class wxsListbook : public wxsContainer
{
    public:

        wxsListbook(wxsItemResData* Data);

    private:

        virtual void OnEnumContainerProperties(long Flags);
        virtual bool OnCanAddChild(wxsItem* Item,bool ShowMessage);
        virtual wxsPropertyContainer* OnBuildExtra();
        virtual wxString OnXmlGetExtraObjectClass();
        virtual void OnAddChildQPP(wxsItem* Child,wxsAdvQPP* QPP);
        virtual wxObject* OnBuildPreview(wxWindow* Parent,long PreviewFlags);
        virtual void OnBuildCreatingCode();
        virtual bool OnMouseClick(wxWindow* Preview,int PosX,int PosY);
        virtual bool OnIsChildPreviewVisible(wxsItem* Child);
        virtual bool OnEnsureChildPreviewVisible(wxsItem* Child);

        void UpdateCurrentSelection();

        wxsItem* m_CurrentSelection;
};

#endif
