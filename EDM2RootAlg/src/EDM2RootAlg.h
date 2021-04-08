#ifndef FIRST_ALG_H
#define FIRST_ALG_H

#include "SniperKernel/AlgBase.h"
#include "EvtNavigator/NavBuffer.h"
#include "TFile.h"
#include "TTree.h"
class EDM2RootAlg : public AlgBase
{
    public :

        EDM2RootAlg(const std::string& name);

        bool initialize();
        bool execute();
        bool finalize();

    private :
         int t_evtID;
         int t_cdhits;
         std::vector<double> t_hittime;
         std::vector<double> t_pmtid;
         TFile * f;
         TTree * h;
         std::string outputfile;
         JM::NavBuffer* m_buf;
};

#endif
