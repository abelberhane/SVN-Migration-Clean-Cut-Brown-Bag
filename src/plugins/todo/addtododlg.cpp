/*
 * This file is part of the Code::Blocks IDE and licensed under the GNU General Public License, version 3
 * http://www.gnu.org/licenses/gpl-3.0.html
 *
 * $Revision: 13091 $
 * $Id: addtododlg.cpp 13091 2022-12-03 08:40:20Z wh11204 $
 * $HeadURL: https://svn.code.sf.net/p/codeblocks/code/trunk/src/plugins/todo/addtododlg.cpp $
 */

#include "sdk.h"
#ifndef CB_PRECOMP
  #include <wx/arrstr.h>
  #include <wx/checkbox.h>
  #include <wx/choice.h>
  #include <wx/intl.h>
  #include <wx/spinctrl.h>
  #include <wx/textctrl.h>
  #include <wx/xrc/xmlres.h>

  #include "manager.h"
  #include "configmanager.h"
  #include "globals.h"
#endif
#include "addtododlg.h"

BEGIN_EVENT_TABLE(AddTodoDlg, wxScrollingDialog)
    EVT_BUTTON(XRCID("btAddUser"), AddTodoDlg::OnAddUser)
    EVT_BUTTON(XRCID("btDelUser"), AddTodoDlg::OnDelUser)
    EVT_BUTTON(XRCID("btAddType"), AddTodoDlg::OnAddType)
    EVT_BUTTON(XRCID("btDelType"), AddTodoDlg::OnDelType)
END_EVENT_TABLE()

AddTodoDlg::AddTodoDlg(wxWindow* parent, const wxArrayString& users, const wxArrayString& types, std::bitset<(int)tdctError+1> supportedTdcts) :
    m_supportedTdcts(supportedTdcts)
{
    wxXmlResource::Get()->LoadObject(this, parent, "dlgAddToDo", "wxScrollingDialog");

    ConfigManager* mgr = Manager::Get()->GetConfigManager("todo_list");
    const wxString lastUser  = mgr->Read("last_used_user");
    const wxString lastType  = mgr->Read("last_used_type");
    const wxString lastStyle = mgr->Read("last_used_style");
    const wxString lastPos   = mgr->Read("last_used_position");
    const bool lastDateReq   = mgr->ReadBool("last_date_req", false);

    // load users
    wxChoice* cmb = XRCCTRL(*this, "chcUser", wxChoice);
    cmb->Clear();

    if (users.empty())
        cmb->Append(wxGetUserId());
    else
        cmb->Append(users);

    if (users.Index(lastUser) == wxNOT_FOUND)
        cmb->SetSelection(0);
    else
        cmb->SetStringSelection(lastUser);

    // load types
    cmb = XRCCTRL(*this, "chcType", wxChoice);
    cmb->Clear();

    if (types.empty())
    {
        cmb->Append("TODO");
        cmb->Append("@todo");
        cmb->Append("\\todo");

        cmb->Append("FIXME");
        cmb->Append("@fixme");
        cmb->Append("\\fixme");

        cmb->Append("NOTE");
        cmb->Append("@note");
        cmb->Append("\\note");
    }
    else
        cmb->Append(types);

    if (types.Index(lastType) == wxNOT_FOUND)
        cmb->SetSelection(0);
    else
        cmb->SetStringSelection(lastType);

    cmb = XRCCTRL(*this, "chcStyle", wxChoice);
    cmb->Clear();
    if (m_supportedTdcts[(int)tdctLine])
        cmb->Append(_("Line comment"));
    if (m_supportedTdcts[(int)tdctStream])
        cmb->Append(_("Stream comment"));
    if (m_supportedTdcts[(int)tdctDoxygenLine])
        cmb->Append(_("Doxygen line comment"));
    if (m_supportedTdcts[(int)tdctDoxygenStream])
        cmb->Append(_("Doxygen stream comment"));
    if (m_supportedTdcts[(int)tdctWarning])
        cmb->Append(_("Compiler warning"));
    if (m_supportedTdcts[(int)tdctError])
            cmb->Append(_("Compiler error"));

    if (lastStyle.empty())
        cmb->SetSelection(0);
    else
        cmb->SetStringSelection(lastStyle);

    cmb = XRCCTRL(*this, "chcPosition", wxChoice);
    if (!lastPos.empty())
        cmb->SetStringSelection(lastPos);

    XRCCTRL(*this, "ID_CHECKBOX1", wxCheckBox)->SetValue(lastDateReq);
}

wxString AddTodoDlg::GetText() const
{
    return XRCCTRL(*this, "txtText", wxTextCtrl)->GetValue();
}

wxString AddTodoDlg::GetUser() const
{
    return XRCCTRL(*this, "chcUser", wxChoice)->GetStringSelection();
}

int AddTodoDlg::GetPriority() const
{
    const int prio = XRCCTRL(*this, "spnPriority", wxSpinCtrl)->GetValue();

    if (prio < 1)
        return 1;

    if(prio > 9)
        return 9;

    return prio;
}

ToDoPosition AddTodoDlg::GetPosition() const
{
    return (ToDoPosition)(XRCCTRL(*this, "chcPosition", wxChoice)->GetSelection());
}

wxString AddTodoDlg::GetType() const
{
    return XRCCTRL(*this, "chcType", wxChoice)->GetStringSelection();
}

ToDoCommentType AddTodoDlg::GetCommentType() const
{
    wxChoice* cmb = XRCCTRL(*this, "chcStyle", wxChoice);

    int sel = cmb->GetSelection();
    for ( int i = 0; i < (int)tdctError ; ++i)
    {
        if (!m_supportedTdcts[i] && sel >= i)
            ++sel;
    }

    return (ToDoCommentType)(sel);
}

void AddTodoDlg::EndModal(int retVal)
{
    if (retVal == wxID_OK)
    {
        wxChoice* cmb = XRCCTRL(*this, "chcUser", wxChoice);
        Manager::Get()->GetConfigManager("todo_list")->Write("users", cmb->GetStrings());
        Manager::Get()->GetConfigManager("todo_list")->Write("last_used_user", cmb->GetStringSelection());

        cmb = XRCCTRL(*this, "chcType", wxChoice);
        Manager::Get()->GetConfigManager("todo_list")->Write("types", cmb->GetStrings());
        Manager::Get()->GetConfigManager("todo_list")->Write("last_used_type", cmb->GetStringSelection());

        cmb = XRCCTRL(*this, "chcStyle", wxChoice);
        Manager::Get()->GetConfigManager("todo_list")->Write("last_used_style", cmb->GetStringSelection());

        cmb = XRCCTRL(*this, "chcPosition", wxChoice);
        Manager::Get()->GetConfigManager("todo_list")->Write("last_used_position", cmb->GetStringSelection());

        wxCheckBox *checkAddDate = XRCCTRL(*this, "ID_CHECKBOX1", wxCheckBox);
        Manager::Get()->GetConfigManager("todo_list")->Write("last_date_req", checkAddDate->GetValue() );
    }

    wxScrollingDialog::EndModal(retVal);
}

void AddTodoDlg::OnAddUser(wxCommandEvent&)
{
    // ask for the new user to be added to the "choice" list
    const wxString &User = cbGetTextFromUser(_("Enter the user you wish to add"), _("Add user"), wxEmptyString, this);
    if (!User.empty())
        XRCCTRL(*this, "chcUser", wxChoice)->Append(User);
}

void AddTodoDlg::OnDelUser(wxCommandEvent&)
{
    wxChoice* cmb = XRCCTRL(*this, "chcUser", wxChoice);
    const int sel = cmb->GetCurrentSelection();
    if (sel == wxNOT_FOUND)
        return;

    wxString msg;
    msg.Printf(_("Are you sure you want to delete the user '%s'?"), cmb->GetString(sel));
    if (cbMessageBox(msg, _("Confirmation"), wxICON_QUESTION | wxYES_NO, this) == wxID_NO)
       return;

    cmb->Delete(sel);
    cmb->SetSelection(0);
}

void AddTodoDlg::OnAddType(wxCommandEvent&)
{
    // ask for the new type to be added to the "choice" list
    const wxString &Type = cbGetTextFromUser(_("Enter the type you wish to add"), _("Add type"), wxEmptyString, this);
    if (!Type.empty())
        XRCCTRL(*this, "chcType", wxChoice)->Append(Type);
}

void AddTodoDlg::OnDelType(wxCommandEvent&)
{
    wxChoice* cmb = XRCCTRL(*this, "chcType", wxChoice);
    const int sel = cmb->GetSelection();
    if (sel == wxNOT_FOUND)
        return;

    wxString msg;
    msg.Printf(_("Are you sure you want to delete the type '%s'?"), cmb->GetString(sel));
    if (cbMessageBox(msg, _("Confirmation"), wxICON_QUESTION | wxYES_NO, this) == wxID_NO)
       return;

    cmb->Delete(sel);
    cmb->SetSelection(0);
}

bool AddTodoDlg::DateRequested() const
{
    return XRCCTRL(*this, "ID_CHECKBOX1", wxCheckBox)->IsChecked();
}
