import sys
import os

dev=["rz","rz_pdep","rz_pin", "vrvz","vrvz_pdep","vrvz_pin", "rvz", "rvz_p", "rvz_rcut", "rvz_rcut_p", "vrvz_rcut", "vrvz_rcut_p", "xy_rcut", "xy_rcut_p", "ke_rcut", "r_rcut"]
dev_type=["TH2D", "TH2D", "TH2D","TH2D", "TH2D", "TH2D", "TH2D", "TH2D","TH2D","TH2D","TH2D","TH2D","TH2D","TH2D","TH1D", "TH1D"]
particle=["all", "electron", "photon", "neutron"]
energy=["all", "lowene", "midene", "highene"]


jsub="/home/rahmans/analysis/BeampipeAnalysis/analyse"
tmp="/global/scratch/rahmans/tmp/analysis"
event=sys.argv[1]
n=int(event)*10000;


for i in range(0,len(dev)):
 for j in particle:
  for k in energy:
   jsubf=open(jsub+"/jsub/"+dev[i]+"_"+event+"_"+j+"_"+k+".pbs", "w")
   jsubf.write("#!/bin/bash\n")
   jsubf.write("#PBS -S /bin/bash\n")
   jsubf.write("#PBS -o "+tmp+"/"+dev[i]+"_"+event+"_"+j+"_"+k+".out\n")
   jsubf.write("#PBS -e "+tmp+"/"+dev[i]+"_"+event+"_"+j+"_"+k+".err\n") 
   jsubf.write("# Script for running target analysis\n")
   jsubf.write("cd "+jsub+"\n")
   jsubf.write("echo \"Current working directory is `pwd`\"\n")
   jsubf.write("echo \"Node file: $PBS_NODEFILE:\"\n")
   jsubf.write("echo \"-----------------------------\"\n")
   jsubf.write("cat $PBS_NODEFILE\n")
   jsubf.write("echo \"-----------------------------\"\n")   
   jsubf.write("CORES=`/bin/awk 'END {print NR}' $PBS_NODEFILE`\n")
   jsubf.write("echo \"Running on $CORES cores.\"\n")
   jsubf.write("echo \"Starting run at: `date`\"\n")
   jsubf.write("module load root-cern/6.14.04-gcc52 geant4/10.4-p02-threads\n") 
   jsubf.write("export OMP_NUM_THREADS=$CORES\n")
   jsubf.write("root -q -b -l "+jsub+"/multiple_hybrid.C'(\""+dev[i]+"\",\""+dev_type[i]+"\",\""+j+"\", \""+k+"\","+str(n)+")'\n")
   jsubf.write("echo \"Program analysis finished with exit code $? at: `date`\"\n")
   jsubf.close()
	                                
   os.system("qsub -l nodes=1:ppn=4,pmem=3gb,walltime=0:05:00 "+jsub+"/jsub/"+dev[i]+"_"+event+"_"+j+"_"+k+".pbs")



