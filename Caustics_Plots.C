//This is a root Program to Plot the Caustics Patterns from the phonon_hits.txt
void Caustics_Plots(){
  ifstream in;
  TString B= "phonon_hits.tx";
  in.open(Form(B));
  Int_t nlines = 0;

   Double_t X_i,Y_i,Z_i;


  while (1) {

     in>>X_i>>Y_i>>Z_i;

     if (!in.good()) break;
  nlines++;
  }
  printf(" found %d points\n",nlines);
in.close();

}
