//----------------------------------------------------------------------
//                             RootTuple
//  Author:  David Hall
//  Date:    29th August 2012
//  Website: http://roottuple.hepforge.org/
//
//  This is the implementation of the RootTuple class.
//
//----------------------------------------------------------------------

#include "RootTuple.h"

//--------------------------------------------------------------
//                        Public methods
//--------------------------------------------------------------
RootTuple::RootTuple() :
m_filename("output.root"), m_treename("tree")
{
}//Constructor

RootTuple::RootTuple(std::string filename, std::string treename) :
m_filename(filename), m_treename(treename)
{
	if (treename.empty()){
		std::cout << "RootTuple:: Warning: Using default tree name" << std::endl;
		m_treename = "tree";
	}
	std::string fileExtension = ".root";
	if (filename.length() <= fileExtension.length()){
		std::cout << "RootTuple:: Warning: Using default file name" << std::endl;
		m_filename = "output.root";
	}
	if (filename.compare(filename.length() - fileExtension.length(), fileExtension.length(), fileExtension) != 0){
		m_filename = filename + ".root";
	}
}//Constructor

RootTuple::~RootTuple()
{
}//Destructor

void RootTuple::Initialise()
{
	// Create TFile object
	m_file = new TFile(m_filename.c_str(), "RECREATE");
	if (!m_file){
		std::cout << "RootTuple:: Error: Cannot create ROOT file" << std::endl;
		return;
	}

	// Create TTree object
	m_tree = new TTree(m_treename.c_str(), m_treename.c_str());
	if (!m_tree)
		std::cout << "RootTuple:: Error: Cannot create ROOT tree" << std::endl;

	DeclareBranches();
}//Initialise

void RootTuple::AddEvent()
{
	// Add data to file and reset vectors
	FillBranches();
	ClearVectors();
}//AddEvent

void RootTuple::Write()
{
	if (m_file)
		m_file->Write();
	else
		std::cout << "RootTuple:: Error: No ROOT file was opened" << std::endl;
}//Write

void RootTuple::Close()
{
	if (m_file){
		m_file->Write();
		m_file->Close();
		delete m_file;
	}
	else
		std::cout << "RootTuple:: Error: No ROOT file was opened" << std::endl;
}//Close
 //
void RootTuple::AddParticle(
    int barcode, int ID, int UID, int history,
    int charge, double mass,
    double px, double py, double pz, 
    double e, double x, double y, double z,
    int event0, int event1, int first_event,
    double last_coll_time, double prod_time, double form_time,
    double scale_cs, double offshell_par)
{
  m_barcode.push_back(barcode);
  m_ID.push_back(ID);
  m_UID.push_back(UID);
  m_history.push_back(history);

  m_charge.push_back(charge);
  m_mass.push_back(mass);

  m_E.push_back(e);
  m_Px.push_back(px);
  m_Py.push_back(py);
  m_Pz.push_back(pz);

  m_x.push_back(x);
  m_y.push_back(y);
  m_z.push_back(z);

  m_event0.push_back(event0);
  m_event1.push_back(event1);
  m_first_event.push_back(first_event);

  m_last_coll_time.push_back(last_coll_time);
  m_prod_time.push_back(prod_time);
  m_form_time.push_back(form_time);

  m_scale_cs.push_back(scale_cs);
  m_offshell_par.push_back(offshell_par);
}//AddParticle  

void RootTuple::SetWeight(double weight)
{
	m_weight = weight;
}//SetWeight

void RootTuple::SetDoubleBranch(std::string branchname, double *ptr)
{
	if (m_tree->GetBranch(branchname.c_str()))
		m_tree->GetBranch(branchname.c_str())->SetAddress(ptr);
	else
		m_tree->Branch(branchname.c_str(), ptr);
}//SetDoubleBranch

void RootTuple::SetFloatBranch(std::string branchname, float *ptr)
{
	if (m_tree->GetBranch(branchname.c_str()))
		m_tree->GetBranch(branchname.c_str())->SetAddress(ptr);
	else
		m_tree->Branch(branchname.c_str(), ptr);
}//SetDoubleBranch

void RootTuple::SetIntBranch(std::string branchname, int *ptr)
{
	if (m_tree->GetBranch(branchname.c_str()))
		m_tree->GetBranch(branchname.c_str())->SetAddress(ptr);
	else
		m_tree->Branch(branchname.c_str(), ptr);
}//SetDoubleBranch

void RootTuple::SetBoolBranch(std::string branchname, bool *ptr)
{
	if (m_tree->GetBranch(branchname.c_str()))
		m_tree->GetBranch(branchname.c_str())->SetAddress(ptr);
	else
		m_tree->Branch(branchname.c_str(), ptr);
}//SetDoubleBranch

//--------------------------------------------------------------
//                       Private methods
//--------------------------------------------------------------
void RootTuple::DeclareBranches()
{
	// Declare required branches
m_tree->Branch("weight",         &m_weight);

m_tree->Branch("pdg_id",         &m_barcode);
m_tree->Branch("gibuu_id",       &m_ID);
m_tree->Branch("particle_id",    &m_UID);
m_tree->Branch("history",        &m_history);

m_tree->Branch("charge",         &m_charge);
m_tree->Branch("mass",           &m_mass);

m_tree->Branch("Px",             &m_Px);
m_tree->Branch("Py",             &m_Py);
m_tree->Branch("Pz",             &m_Pz);
m_tree->Branch("E",              &m_E);

m_tree->Branch("x",              &m_x);
m_tree->Branch("y",              &m_y);
m_tree->Branch("z",              &m_z);

m_tree->Branch("event0",         &m_event0);
m_tree->Branch("event1",         &m_event1);
m_tree->Branch("first_event",    &m_first_event);

m_tree->Branch("last_coll_time", &m_last_coll_time);
m_tree->Branch("prod_time",      &m_prod_time);
m_tree->Branch("form_time",      &m_form_time);

m_tree->Branch("scale_cs",       &m_scale_cs);
m_tree->Branch("offshell_par",   &m_offshell_par);
}//DeclareBranches

void RootTuple::FillBranches()
{
	if(m_tree)
		m_tree->Fill();
}//FillBranches

void RootTuple::ClearVectors()
{
	m_barcode.clear();
	m_ID.clear();
  m_UID.clear();
  m_history.clear();

	m_Px.clear();
	m_Py.clear();
	m_Pz.clear();
	m_E.clear();

  m_x.clear();
  m_y.clear();
  m_z.clear();

  m_mass.clear();
  m_charge.clear();

  m_event0.clear();
  m_event1.clear();
  m_first_event.clear();

  m_last_coll_time.clear();
  m_prod_time.clear();
  m_form_time.clear();

  m_scale_cs.clear();
  m_offshell_par.clear();
}//ClearVectors
