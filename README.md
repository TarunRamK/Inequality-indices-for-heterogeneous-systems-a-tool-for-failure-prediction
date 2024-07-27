# Inequality-indices-for-heterogeneous-systems-a-tool-for-failure-prediction
Codes used in the paper "Inequality indices for heterogeneous systems: a tool for failure prediction" by Tarun Ram Kanuri, Subhadeep Roy, Soumyajyoti Biswas
========================================================================================================================


Delta:
------
bash_delta.c: This C code creates the simulation files (systems) for delta distribution.
bijun_find_cri_value.h: Code to find critical value for the system. Not used.
g_and_k.ipynb: Uses the theoretical calculations and results from "g_f_finder" and "k_f_finder" to draw graphs.
g_f_finder: Used to find the Gini index for a set of systems created by "bash_delta.c".
k_f_finder: Used to find the Kolkata index for a set of systems created by "bash_delta.c".

Uniform:
--------
bash_uniform_with_cri.c: This C code creates the simulation files (systems) for uniform distribution.
bijun_find_cri_value.h: Code to find critical value for the system.
g_and_k.ipynb: Uses the theoretical calculations and results from "g_f_finder" and "k_f_finder" to draw graphs.
g_f_finder: Used to find the Gini index for a set of systems created by "bash_uniform_with_cri.c".
k_f_finder: Used to find the Kolkata index for a set of systems created by "bash_uniform_with_cri.c".

Weibull:
--------
bash_weibull_with_cri.c: This C code creates the simulation files (systems) for Weibull distribution.
bijun_find_cri_value.h: Code to find critical value for the system.
g_and_k.ipynb: Uses the theoretical calculations and results from "g_f_finder" and "k_f_finder" to draw graphs.
g_f_finder: Used to find the Gini index for a set of systems created by "bash_uniform_with_cri.c".
k_f_finder: Used to find the Kolkata index for a set of systems created by "bash_uniform_with_cri.c".

Others:
-------


Note: The folders "Delta", "Uniform" and "Weibull" each contain 5 files, out of which 3 are identical while the remaining 2 files differ slightly. The files named "g_and_k.ipynb", "g_f_finder.py", and "k_f_finder.py" in one folder are identical to the files with the same name from different folders. The files named "g_and_k.ipynb", "g_f_finder.py", and "k_f_finder.py" in the "Delta" folder are the same as those from the "Uniform" and "Weibull" folders.
