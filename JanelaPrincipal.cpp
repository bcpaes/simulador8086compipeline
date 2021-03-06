#include "JanelaPrincipal.h"

//(*InternalHeaders(JanelaPrincipal)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(JanelaPrincipal)
const long JanelaPrincipal::ID_BUTTON1 = wxNewId();
const long JanelaPrincipal::ID_BUTTON2 = wxNewId();
const long JanelaPrincipal::ID_STATICLINE1 = wxNewId();
const long JanelaPrincipal::ID_STATICLINE2 = wxNewId();
const long JanelaPrincipal::ID_BUTTON3 = wxNewId();
const long JanelaPrincipal::ID_LISTCTRL2 = wxNewId();
const long JanelaPrincipal::ID_LISTCTRL1 = wxNewId();
const long JanelaPrincipal::ID_BUTTON4 = wxNewId();
const long JanelaPrincipal::ID_LISTCTRL3 = wxNewId();
const long JanelaPrincipal::ID_STATICTEXT1 = wxNewId();
const long JanelaPrincipal::ID_STATICTEXT2 = wxNewId();
const long JanelaPrincipal::ID_STATICTEXT3 = wxNewId();
const long JanelaPrincipal::ID_PANEL1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(JanelaPrincipal,wxFrame)
	//(*EventTable(JanelaPrincipal)
	//*)
END_EVENT_TABLE()

JanelaPrincipal::JanelaPrincipal(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(JanelaPrincipal)
	Create(parent, id, _("Simulador 8086 com pipeline"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
	SetClientSize(wxSize(800,460));
	Move(wxDefaultPosition);
	Panel1 = new wxPanel(this, ID_PANEL1, wxPoint(0,0), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
	Button1 = new wxButton(Panel1, ID_BUTTON1, _("Sobre"), wxPoint(704,8), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	Abrir = new wxButton(Panel1, ID_BUTTON2, _("Abrir"), wxPoint(704,48), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	StaticLine1 = new wxStaticLine(Panel1, ID_STATICLINE1, wxPoint(704,42), wxSize(88,2), wxLI_HORIZONTAL, _T("ID_STATICLINE1"));
	StaticLine2 = new wxStaticLine(Panel1, ID_STATICLINE2, wxPoint(704,82), wxSize(88,2), wxLI_HORIZONTAL, _T("ID_STATICLINE2"));
	Executar = new wxButton(Panel1, ID_BUTTON3, _("Executar"), wxPoint(704,88), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
	Registradores = new wxListCtrl(Panel1, ID_LISTCTRL2, wxPoint(8,32), wxSize(680,72), wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_HRULES|wxLC_VRULES|wxRAISED_BORDER, wxDefaultValidator, _T("ID_LISTCTRL2"));
	Pipeline = new wxListCtrl(Panel1, ID_LISTCTRL1, wxPoint(8,224), wxSize(680,224), wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_HRULES|wxLC_VRULES|wxRAISED_BORDER, wxDefaultValidator, _T("ID_LISTCTRL1"));
	Resetar = new wxButton(Panel1, ID_BUTTON4, _("Resetar"), wxPoint(704,128), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON4"));
	Flags = new wxListCtrl(Panel1, ID_LISTCTRL3, wxPoint(8,136), wxSize(680,56), wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_HRULES|wxLC_VRULES|wxRAISED_BORDER, wxDefaultValidator, _T("ID_LISTCTRL3"));
	StaticText1 = new wxStaticText(Panel1, ID_STATICTEXT1, _("Registradores:"), wxPoint(8,8), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	StaticText2 = new wxStaticText(Panel1, ID_STATICTEXT2, _("Flags:"), wxPoint(8,112), wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	StaticText3 = new wxStaticText(Panel1, ID_STATICTEXT3, _("Pipeline:"), wxPoint(8,200), wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	Center();

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&JanelaPrincipal::OnButton1Click);
	Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&JanelaPrincipal::OnResetarClick);
	//*)
    Reset();
}

JanelaPrincipal::~JanelaPrincipal()
{
	//(*Destroy(JanelaPrincipal)
	//*)
}


void JanelaPrincipal::OnButton1Click(wxCommandEvent& event)
{
    JanelaSobre dialog(this);
    dialog.ShowModal();
}

void JanelaPrincipal::Reset()
{
    Registradores->ClearAll();
    Registradores->InsertColumn(0,_("AX"));     //Acumulator
	Registradores->InsertColumn(1,_("BX"));     //Base Address
	Registradores->InsertColumn(2,_("CX"));     //Count
	Registradores->InsertColumn(3,_("DX"));     //Data  (Em alguns casos os registradores DX:AX são concatenados formando um registrador de 32bits para ser usado em instruções como MUL e DIV)
	Registradores->InsertColumn(4,_("CS"));     //Current Segment
	Registradores->InsertColumn(5,_("IP"));     //Instruction Pointer
	Registradores->InsertColumn(6,_("SS"));     //Stack Segment Pointer
	Registradores->InsertColumn(7,_("SP"));     //Stack Pointer
    Registradores->InsertColumn(8,_("BP"));     //Base Pointer
	Registradores->InsertColumn(9,_("SI"));     //Souce Index
	Registradores->InsertColumn(10,_("DI"));    //Destination Index
	Registradores->InsertColumn(11,_("DS"));    //General Segment
	Registradores->InsertColumn(12,_("ES"));    //Extra Segment

	Registradores->InsertItem(0,_("0000h"));    //AX
	Registradores->SetItem(0,1,_("0000h"));     //BX
    Registradores->SetItem(0,2,_("0000h"));     //CX
    Registradores->SetItem(0,3,_("0000h"));     //DX
    Registradores->SetItem(0,4,_("0050h"));     //CS 0050
	Registradores->SetItem(0,5,_("0000h"));     //IP
    Registradores->SetItem(0,6,_("0000h"));     //SS
    Registradores->SetItem(0,7,_("0000h"));     //SP
    Registradores->SetItem(0,8,_("0000h"));     //BP
    Registradores->SetItem(0,9,_("0000h"));     //SI
	Registradores->SetItem(0,10,_("0000h"));     //DI
    Registradores->SetItem(0,11,_("0000h"));     //DS
    Registradores->SetItem(0,12,_("0000h"));     //ES

    Pipeline->ClearAll();
    Pipeline->InsertColumn(0,_("IF"));          //Instruction Fetch
    Pipeline->InsertColumn(1,_("ID"));          //Instruction Decode
    Pipeline->InsertColumn(2,_("EX"));          //Execute
    Pipeline->InsertColumn(3,_("MEM"));         //Memory Access
    Pipeline->InsertColumn(4,_("WB"));          //Register Write Back

    Flags->ClearAll();
    Flags->InsertColumn(0,_("CF"));             //Carry
    Flags->InsertColumn(1,_("ZF"));             //Zero
    Flags->InsertColumn(2,_("SF"));             //Sign
    Flags->InsertColumn(3,_("OF"));             //Overflow
    Flags->InsertColumn(4,_("PF"));             //Parity
    Flags->InsertColumn(5,_("AF"));             //Auxiliary Carry
    Flags->InsertColumn(6,_("IF"));             //Interupt
    Flags->InsertColumn(7,_("DF"));             //Direction

    Flags->InsertItem(0,_("0"));                //CF
    Flags->SetItem(0,1,_("0"));                 //ZF
    Flags->SetItem(0,2,_("0"));                 //SF
    Flags->SetItem(0,3,_("0"));                 //OF
    Flags->SetItem(0,4,_("0"));                 //PF
    Flags->SetItem(0,5,_("0"));                 //AF
    Flags->SetItem(0,6,_("1"));                 //IF 1
    Flags->SetItem(0,7,_("0"));                 //DF
}

void JanelaPrincipal::OnResetarClick(wxCommandEvent& event)
{
    Reset();
}
