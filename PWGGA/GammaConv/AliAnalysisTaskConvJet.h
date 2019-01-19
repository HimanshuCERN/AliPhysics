#ifndef AliAnalysisTaskConvJet_H
#define AliAnalysisTaskConvJet_H
/**
 * \file AliAnalysisTaskConvJet.h
 *
 * \author Lizette Lamers <lizette.jacqueline.lamers@cern.ch>, Utrecht University
 * \author Mike Sas <mike.sas@cern.ch>, Utrecht University
 * \date Okt 4, 2018
 */

/* Copyright(c) 1998-2016, ALICE Experiment at CERN, All rights reserved. *
 * See cxx source for full Copyright notice                               */

using namespace std;
#include "AliAnalysisTaskEmcalJet.h"
#include "THistManager.h"

/**
 * \class AliAnalysisTaskConvJet
 * \brief Implementation of a sample jet analysis task.
 *
 * This class in an implementation of a sample task for EMCal jet analysis.
 * It derives from AliAnalysisTaskEmcalJet.
 * It performs a simple analysis, producing jet spectra.
 */
class AliAnalysisTaskConvJet : public AliAnalysisTaskEmcalJet {
 public:

  AliAnalysisTaskConvJet(Int_t IsMC)                                     ;
  AliAnalysisTaskConvJet(const char *name, Int_t IsMC)                   ;
  ~AliAnalysisTaskConvJet(){
     delete  fJetNameArray;
     delete  fTrueJetNameArray;
     delete  fTrainconfigArray;
     delete  fTrueTrainconfigArray;
  }

  void                        UserCreateOutputObjects()                         ;
  void                        Terminate(Option_t *option)                       ;

  static AliAnalysisTaskConvJet* AddTask_GammaConvJet(
      const char *ntracks            = "usedefault",
      const char *nclusters          = "usedefault",
      const char* ncells             = "usedefault",
      const char *suffix             = "",
      Int_t IsMC                     = 0,
      Int_t NContainers              = 0);

  void SetNumberOfContainers(Int_t NContainers){
      if(fIsMC == 0){
        fNJetContainers = NContainers;
        fTrainconfigArray = new Int_t[fNJetContainers];
        fJetNameArray = new TString[fNJetContainers];
      }else{
        fNJetContainers = NContainers/2;
        fNTrueJetContainers = NContainers/2;
        fTrainconfigArray = new Int_t[fNJetContainers];
        fJetNameArray = new TString[fNJetContainers];
        fTrueTrainconfigArray = new Int_t[fNTrueJetContainers];
        fTrueJetNameArray = new TString[fNTrueJetContainers];
      }
  }

  void AddJetContainerwithTrainConfig(TString JetContainerName, Int_t Trainconfig, Double_t Radius){
      TString Add = "_";
      Add.Append(JetContainerName);
      Add.Append("_pT1000");
        if(fJetContainersAdded < fNJetContainers){
          AddJetContainer(JetContainerName, AliEmcalJet::kTPCfid, Radius);
          fJetNameArray[fJetContainersAdded] = Add;
          fTrainconfigArray[fJetContainersAdded] = Trainconfig;
          vector<Double_t> JetPt;
          fListJetPt.push_back(JetPt);
          vector<Double_t> JetPx;
          fListJetPx.push_back(JetPx);
          vector<Double_t> JetPy;
          fListJetPy.push_back(JetPy);
          vector<Double_t> JetPz;
          fListJetPz.push_back(JetPz);
          vector<Double_t> JetEta;
          fListJetEta.push_back(JetEta);
          vector<Double_t> JetPhi;
          fListJetPhi.push_back(JetPhi);
          vector<Double_t> JetArea;
          fListJetArea.push_back(JetArea);
          fListNJets.push_back(0);
          fJetContainersAdded++;
        }
  }

  void AddTrueandRecJetContainerwithTrainConfig(TString RecJetContainerName, TString TrueJetContainerName, Int_t Trainconfig, Double_t Radius){
      AliJetContainer* jetContRec;
      AliJetContainer* jetContTrue;
      TString AddRec = "_";
      AddRec.Append(RecJetContainerName);
      AddRec.Append("_pT1000");
      TString AddTrue = "_";
      AddTrue.Append(TrueJetContainerName);
      AddTrue.Append("_pT1000");
      if(fJetContainersAdded < fNJetContainers){
        jetContRec = AddJetContainer(RecJetContainerName, AliEmcalJet::kTPCfid, Radius);
        fJetNameArray[fJetContainersAdded] = AddRec;
        fTrainconfigArray[fJetContainersAdded] = Trainconfig;
        vector<Double_t> JetPt;
        fListJetPt.push_back(JetPt);
        vector<Double_t> JetPx;
        fListJetPx.push_back(JetPx);
        vector<Double_t> JetPy;
        fListJetPy.push_back(JetPy);
        vector<Double_t> JetPz;
        fListJetPz.push_back(JetPz);
        vector<Double_t> JetEta;
        fListJetEta.push_back(JetEta);
        vector<Double_t> JetPhi;
        fListJetPhi.push_back(JetPhi);
        vector<Double_t> JetArea;
        fListJetArea.push_back(JetArea);
        fListNJets.push_back(0);
        fJetContainersAdded++;
      }
      if(fTrueJetContainersAdded < fNTrueJetContainers){
        AliParticleContainer *trackCont = AddParticleContainer("tracks");
        AliClusterContainer *clusterCont = AddClusterContainer("caloClusters");
        jetContRec->ConnectParticleContainer(trackCont);
        jetContRec->ConnectClusterContainer(clusterCont);
        jetContTrue = AddJetContainer(TrueJetContainerName, AliEmcalJet::kTPCfid, Radius);
        jetContTrue->ConnectParticleContainer(trackCont);
        jetContTrue->ConnectClusterContainer(clusterCont);
        fTrueJetNameArray[fTrueJetContainersAdded] = AddTrue;
        fTrueTrainconfigArray[fTrueJetContainersAdded] = Trainconfig;
        vector<Double_t> JetPt;
        fListTrueJetPt.push_back(JetPt);
        vector<Double_t> JetPx;
        fListTrueJetPx.push_back(JetPx);
        vector<Double_t> JetPy;
        fListTrueJetPy.push_back(JetPy);
        vector<Double_t> JetPz;
        fListTrueJetPz.push_back(JetPz);
        vector<Double_t> JetEta;
        fListTrueJetEta.push_back(JetEta);
        vector<Double_t> JetPhi;
        fListTrueJetPhi.push_back(JetPhi);
        vector<Double_t> JetArea;
        fListTrueJetArea.push_back(JetArea);
        fListTrueNJets.push_back(0);
        fTrueJetContainersAdded++;
      }
  }

  Double_t GetNJets(Int_t Trainconfig) {
      Int_t NJets = 0;
      for(Int_t i = 0; i < fNJetContainers; i++){
        if(Trainconfig == fTrainconfigArray[i]){
          NJets = fListNJets.at(i);
          break;
        }
      }
      return NJets;
}
  vector<Double_t> GetVectorJetPt(Int_t Trainconfig){
      vector<Double_t> VectorJetPt;
      for(Int_t i = 0; i < fNJetContainers; i++){
        if(Trainconfig == fTrainconfigArray[i]){
          VectorJetPt = fListJetPt.at(i);
          break;
        }
      }
      return VectorJetPt;
}
  vector<Double_t> GetVectorJetPx(Int_t Trainconfig){
      vector<Double_t> VectorJetPx;
      for(Int_t i = 0; i < fNJetContainers; i++){
        if(Trainconfig == fTrainconfigArray[i]){
          VectorJetPx = fListJetPx.at(i);
          break;
        }
      }
      return VectorJetPx;
}
  vector<Double_t> GetVectorJetPy(Int_t Trainconfig){
      vector<Double_t> VectorJetPy;
      for(Int_t i = 0; i < fNJetContainers; i++){
        if(Trainconfig == fTrainconfigArray[i]){
          VectorJetPy = fListJetPy.at(i);
          break;
        }
      }
      return VectorJetPy;
}
  vector<Double_t> GetVectorJetPz(Int_t Trainconfig){
      vector<Double_t> VectorJetPz;
      for(Int_t i = 0; i < fNJetContainers; i++){
        if(Trainconfig == fTrainconfigArray[i]){
          VectorJetPz = fListJetPz.at(i);
          break;
        }
      }
      return VectorJetPz;
}
  vector<Double_t> GetVectorJetEta(Int_t Trainconfig){
      vector<Double_t> VectorJetEta;
      for(Int_t i = 0; i < fNJetContainers; i++){
        if(Trainconfig == fTrainconfigArray[i]){
          VectorJetEta = fListJetEta.at(i);
          break;
        }
      }
      return VectorJetEta;
}
  vector<Double_t> GetVectorJetPhi(Int_t Trainconfig){
      vector<Double_t> VectorJetPhi;
      for(Int_t i = 0; i < fNJetContainers; i++){
        if(Trainconfig == fTrainconfigArray[i]){
          VectorJetPhi = fListJetPhi.at(i);
          break;
        }
      }
      return VectorJetPhi;
}
  vector<Double_t> GetVectorJetArea(Int_t Trainconfig){
      vector<Double_t> VectorJetArea;
      for(Int_t i = 0; i < fNJetContainers; i++){
        if(Trainconfig == fTrainconfigArray[i]){
          VectorJetArea = fListJetArea.at(i);
          break;
        }
      }
      return VectorJetArea;
}
//------------------------------------------------------------------
    Double_t GetTrueNJets(Int_t Trainconfig) {
        Int_t NJets = 0;
      for(Int_t i = 0; i < fNTrueJetContainers; i++){
        if(Trainconfig == fTrueTrainconfigArray[i]){
          NJets = fListTrueNJets.at(i);
          break;
        }
      }
      return NJets;
}
  vector<Double_t> GetTrueVectorJetPt(Int_t Trainconfig){
      vector<Double_t> VectorJetPt;
      for(Int_t i = 0; i < fNTrueJetContainers; i++){
        if(Trainconfig == fTrueTrainconfigArray[i]){
          VectorJetPt = fListTrueJetPt.at(i);
          break;
        }
      }
      return VectorJetPt;
}
  vector<Double_t> GetTrueVectorJetPx(Int_t Trainconfig){
      vector<Double_t> VectorJetPx;
      for(Int_t i = 0; i < fNTrueJetContainers; i++){
        if(Trainconfig == fTrueTrainconfigArray[i]){
          VectorJetPx = fListTrueJetPx.at(i);
          break;
        }
      }
      return VectorJetPx;
}
  vector<Double_t> GetTrueVectorJetPy(Int_t Trainconfig){
      vector<Double_t> VectorJetPy;
      for(Int_t i = 0; i < fNTrueJetContainers; i++){
        if(Trainconfig == fTrueTrainconfigArray[i]){
          VectorJetPy = fListTrueJetPy.at(i);
          break;
        }
      }
      return VectorJetPy;
}
  vector<Double_t> GetTrueVectorJetPz(Int_t Trainconfig){
      vector<Double_t> VectorJetPz;
      for(Int_t i = 0; i < fNTrueJetContainers; i++){
        if(Trainconfig == fTrueTrainconfigArray[i]){
          VectorJetPz = fListTrueJetPz.at(i);
          break;
        }
      }
      return VectorJetPz;
}
  vector<Double_t> GetTrueVectorJetEta(Int_t Trainconfig){
      vector<Double_t> VectorJetEta;
      for(Int_t i = 0; i < fNTrueJetContainers; i++){
        if(Trainconfig == fTrueTrainconfigArray[i]){
          VectorJetEta = fListTrueJetEta.at(i);
          break;
        }
      }
      return VectorJetEta;
}
  vector<Double_t> GetTrueVectorJetPhi(Int_t Trainconfig){
      vector<Double_t> VectorJetPhi;
      for(Int_t i = 0; i < fNTrueJetContainers; i++){
        if(Trainconfig == fTrueTrainconfigArray[i]){
          VectorJetPhi = fListTrueJetPhi.at(i);
          break;
        }
      }
      return VectorJetPhi;
}
  vector<Double_t> GetTrueVectorJetArea(Int_t Trainconfig){
      vector<Double_t> VectorJetArea;
      for(Int_t i = 0; i < fNTrueJetContainers; i++){
        if(Trainconfig == fTrueTrainconfigArray[i]){
          VectorJetArea = fListTrueJetArea.at(i);
          break;
        }
      }
      return VectorJetArea;
}
//------------------------------------------------------------------
  Double_t Get_Jet_Radius(Int_t Trainconfig){
      TString JetName;
      for(Int_t i = 0; i < fNTrueJetContainers; i++){
        if(Trainconfig == fTrainconfigArray[i]){
          JetName = fJetNameArray[i];
          break;
        }
      }
      AliJetContainer* jetCont = 0;
      TIter next(&fJetCollArray);
      Double_t radius = -1;
      while ((jetCont = static_cast<AliJetContainer*>(next()))) {
         if(JetName == jetCont->GetTitle()){
           radius = jetCont->GetJetRadius();
           break;
        }
      }
      return radius;
 }

 protected:
  void                        ExecOnce()                                        ;
  Bool_t                      FillHistograms()                                  ;
  Bool_t                      Run()                                             ;
  void                        DoJetLoop()                                       ;

  Int_t fIsMC                                                                   ;
  Int_t fNJetContainers                                                         ;
  Int_t fNTrueJetContainers                                                     ;
  Int_t fJetContainersAdded                                                     ;
  Int_t fTrueJetContainersAdded                                                 ;
  TString *fJetNameArray                                                        ;
  TString *fTrueJetNameArray                                                    ;
  Int_t *fTrainconfigArray                                                      ;
  Int_t *fTrueTrainconfigArray                                                  ;

  vector<Int_t>               fListNJets                                        ;
  vector<vector<Double_t>>    fListJetPt                                        ;
  vector<vector<Double_t>>    fListJetPx                                        ;
  vector<vector<Double_t>>    fListJetPy                                        ;
  vector<vector<Double_t>>    fListJetPz                                        ;
  vector<vector<Double_t>>    fListJetEta                                       ;
  vector<vector<Double_t>>    fListJetPhi                                       ;
  vector<vector<Double_t>>    fListJetArea                                      ;

  vector<Int_t>               fListTrueNJets                                    ;
  vector<vector<Double_t>>    fListTrueJetPt                                    ;
  vector<vector<Double_t>>    fListTrueJetPx                                    ;
  vector<vector<Double_t>>    fListTrueJetPy                                    ;
  vector<vector<Double_t>>    fListTrueJetPz                                    ;
  vector<vector<Double_t>>    fListTrueJetEta                                   ;
  vector<vector<Double_t>>    fListTrueJetPhi                                   ;
  vector<vector<Double_t>>    fListTrueJetArea                                  ;

 private:
  AliAnalysisTaskConvJet(const AliAnalysisTaskConvJet&)           ;
  AliAnalysisTaskConvJet &operator=(const AliAnalysisTaskConvJet&);

  /// \cond CLASSIMP
  ClassDef(AliAnalysisTaskConvJet, 6);
  /// \endcond
};
#endif
