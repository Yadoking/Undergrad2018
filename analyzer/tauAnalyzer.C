#define tauAnalyzer_cxx
#include "tauAnalyzer.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
using namespace std;

void tauAnalyzer::Loop()
{
//   In a ROOT session, you can do:
//      root> .L tauAnalyzer.C
//      root> tauAnalyzer t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch

  if (fChain == 0) return;

  std::vector<int> b_matched_tauTag;

  TFile* f = new TFile("out.root", "recreate");
  TTree* tree = new TTree("tree", "ntuple");

  tree->Branch("matched_tauTag", "std::vector<int>", &b_matched_tauTag);
  TH1F* h_tauTag_matched = new TH1F("tauTag","",2,0,2);

  Long64_t nentries = fChain->GetEntries();
  Long64_t nbytes = 0, nb = 0;

  for(Long64_t jentry=0; jentry<nentries; jentry++) {
    fChain->GetEntry(jentry);
    std::cout << jentry << " / " << nentries << '\r';

    vector<int> matchedIdx;
    TLorentzVector jet;

    for(int i=0; i<nJet; i++){
      if(Jet_pt[i] > 30 && abs(Jet_eta[i]) < 2.4){
        jet.SetPtEtaPhiM(Jet_pt[i],Jet_eta[i],Jet_phi[i], Jet_m[i]);

        TLorentzVector genParticle;
        for(int j=0; j<nGenParticle; j++){
          if(std::abs(GenParticle_pdgId[j]) != 15) continue;
          genParticle.SetPtEtaPhiM(GenParticle_pt[j], GenParticle_eta[j], GenParticle_phi[j], GenParticle_m[j]);
          if(jet.DeltaR(genParticle) < 0.5) matchedIdx.push_back(j);
        }
      }
    }

    for(vector<int>::iterator iter=matchedIdx.begin(); iter!=matchedIdx.end(); ++iter){
      b_matched_tauTag.push_back(Jet_tauTag[*iter]);
			h_tauTag_matched->Fill(Jet_tauTag[*iter]);
    }

    tree->Fill();
    b_matched_tauTag.clear();

  }

  tree->Write();
  h_tauTag_matched->Write();
	f->Close();

}