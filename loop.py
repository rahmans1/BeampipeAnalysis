import sys
import os

conf=["mreal90_conf7"]#["mrealBe_conf7"]#["hmkryp_conf7","hmreal_conf7","mkryp_conf7","mreal_conf7"]#hollowkryp_conf4", "mergedreal_conf7", "hollowmergedreal_conf7","mergedkryp_conf7"]#["real_conf0", "real_conf1", "real_conf2", "real_conf3", "real_conf4", "real_conf5","real_conf6","real_conf7", "kryp_conf0", "kryp_conf1", "kryp_conf2"]
particle=["all", "electron", "photon", "neutron"]
energy=["all", "lowene", "midene", "highene"]



for i in conf:
 for j in particle:
  for k in energy:
   os.system("python group.py \""+i+"\" \""+str(2000)+"\" \""+j+"\" \""+k+"\"");		

