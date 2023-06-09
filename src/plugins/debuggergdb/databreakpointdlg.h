/*
 * This file is part of the Code::Blocks IDE and licensed under the GNU General Public License, version 3
 * http://www.gnu.org/licenses/gpl-3.0.html
 */

#ifndef DATABREAKPOINTDLG_H
#define DATABREAKPOINTDLG_H

#include <wx/wxprec.h>

//(*Headers(DataBreakpointDlg)
#include <wx/checkbox.h>
#include <wx/sizer.h>
#include "scrollingdialog.h"
#include <wx/textctrl.h>
#include <wx/radiobox.h>
//*)

class DataBreakpointDlg: public wxScrollingDialog
{
    public:

        DataBreakpointDlg(wxWindow *parent, const wxString& dataExpression, bool enabled, int selection);
        virtual ~DataBreakpointDlg();

        //(*Identifiers(DataBreakpointDlg)
        static const long ID_CHK_ENABLED;
        static const long ID_TXT_DATA_EXPRESION;
        static const long ID_RDO_CONDITION;
        //*)

        bool IsBreakpointEnabled();
        int GetSelection();
        wxString GetDataExpression() const;

    protected:

        //(*Handlers(DataBreakpointDlg)
        //*)

        //(*Declarations(DataBreakpointDlg)
        wxRadioBox* m_condition;
        wxCheckBox* m_enabled;
        wxTextCtrl* m_dataExpression;
        wxStdDialogButtonSizer* StdDialogButtonSizer1;
        //*)

    private:

        DECLARE_EVENT_TABLE()
};

#endif
