Int_t setupPar(const char* pararchivename);

void LoadLibraries(Bool_t useParFiles=kFALSE) {

  gSystem->Load("libTree");
  gSystem->Load("libGeom");
  gSystem->Load("libPhysics");
  gSystem->Load("libVMC");
  gSystem->Load("libMinuit");
  gSystem->Load("libSTEERBase");
  gSystem->Load("libESD");
  gSystem->Load("libAOD");
  gSystem->Load("libANALYSIS");
  gSystem->Load("libOADB");
  gSystem->Load("libANALYSISalice");
  gSystem->Load("libCORRFW");
  gSystem->Load("libPWGHFbase");
  gSystem->Load("libPWGflowBase");
  gSystem->Load("libPWGflowTasks");
  gSystem->Load("libPWGHFvertexingHF");
  //gSystem->Load("libPWGmuon");
 

  if(useParFiles) {
    setupPar("STEERBase");
    setupPar("ESD");
    setupPar("AOD");
    setupPar("ANALYSIS");
    setupPar("OADB");
    setupPar("ANALYSISalice");
    setupPar("CORRFW");  
    setupPar("PWGHFbase");
    setupPar("PWGHFvertexingHF");
    //setupPar("PWG3muon");
  }

  return;
}
//------------------------------------------------------------------------
Int_t setupPar(const char* pararchivename) {
  ///////////////////
  // Setup PAR File//
  ///////////////////

  if (pararchivename) {
    char processline[1024];
    TString base = gSystem->BaseName(pararchivename);
    TString dir  = gSystem->DirName(pararchivename);
    TString ocwd = gSystem->WorkingDirectory();
    // Move to dir where the par files are and unpack 
    gSystem->ChangeDirectory(dir.Data());
    sprintf(processline,".! tar xvzf %s.par",base.Data());
    gROOT->ProcessLine(processline);
    // Move to par folder                           
    gSystem->ChangeDirectory(base.Data());

    // check for BUILD.sh and execute                
    if (!gSystem->AccessPathName("PROOF-INF/BUILD.sh")) {
      printf("*******************************\n");
      printf("*** Building PAR archive    ***\n");
      printf("*******************************\n");

      if (gSystem->Exec("PROOF-INF/BUILD.sh")) {
        Error("runAnalysis","Cannot Build the PAR Archive! - Abort!");
	gSystem->ChangeDirectory(ocwd.Data());
        return -1;
      }
    }
    // check for SETUP.C and execute                
    if (!gSystem->AccessPathName("PROOF-INF/SETUP.C")) {
      printf("*******************************\n");
      printf("*** Setup PAR archive       ***\n");
      printf("*******************************\n");
      // If dir not empty, set the full include path 
      if (dir.Length()) {
	sprintf(processline, ".include %s", pararchivename);
	gROOT->ProcessLine(processline);
      }
      gROOT->Macro("PROOF-INF/SETUP.C");
    }
    gSystem->ChangeDirectory(ocwd.Data());
  }
  return 1;
}
