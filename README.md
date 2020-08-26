# GEM_relative_efficiency
Contains scripts written by Sean Jeffas to calculate single GEM relative efficiency and the extension of those scripts to calculate SBS-UVA GEM Layer (4 modules at a time) efficiency written by Anurudda Rathnayake.

###"rootlogon.C"###
Loads the macros when ROOT is started
####################################################################################################################################################################

###"simplify.C"###

  For runs with one GEM this takes the Tracking root file makes a simplified file with the important plots.
  It also reads out the number of triggers and hits to be used to make efficiency plots.
 
 ###################################################################################################################################################################
 
 ###"efficiency_plot.C"###
 
  Script to make Relative Efficiency plots vs Voltage for a single GEM module.
 
 ###################################################################################################################################################################
 
 ###"GEM_rel_efficiency.C###
ROOT macro to make "Relative Efficiency vs High Voltage" plots for UVA-SBS GEM layers with 4 SBS gem modules in a layer. Have to use the "rootlogon.C" file to load.
 
Function calling method-> GEM_rel_efficiency(mod1#, mod2#, mod3#, mod4#, mod1_prodID, mod2_prodID, mod3_prodID, mod4_prodID, GEM_layer#)
modx#: Goes from 0 to 19 (For 5 layers in the cosmic stand)
modx_prodID: The production ID given at UVA while GEM fabrication
GEM_layer#: Goes from 0 through 10 (For 11 UVA-SBS GEM layers)
 
