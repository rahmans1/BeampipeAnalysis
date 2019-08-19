import sys
import os

conf=["kryp_conf2"]#"real_conf0", "real_conf1", "real_conf2", "real_conf3", "real_conf4", "real_conf5", "kryp_conf0"]
particle=["all", "electron", "photon", "neutron"]
energy=["all", "lowene", "midene", "highene"]



for i in conf:
 for j in particle:
  for k in energy:
   os.system("python group.py \""+i+"\" \""+str(2000)+"\" \""+j+"\" \""+k+"\"");		

