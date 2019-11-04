if [ ! -d "output/temp" ]; then
	mkdir output/temp
fi
rm -f merged/hist*
mv -f output/hist_TT012Jets_0[0-4][0-9].root output/temp/
mv -f output/hist_TT012Jets_050.root output/temp
mv -f output/hist_LQcmutauLO_00[1-5].root output/temp/
mv -f output/hist_LQctautauLO_00[1-5].root output/temp/
mv -f output/hist_LQcnunuLO_00[1-5].root output/temp/
hadd merged/hist_W1JetsToLNu.root output/hist_W1JetsToLNu*.root
hadd merged/hist_DY012JetsM10toinf.root output/hist_DY012JetsM10toinf*.root
hadd merged/hist_W0JetsToLNu.root output/hist_W0JetsToLNu*.root
hadd merged/hist_W2JetsToLNu.root output/hist_W2JetsToLNu*.root
hadd merged/hist_TT012Jets.root output/hist_TT012Jets*.root
hadd merged/hist_WW.root output/hist_WW*.root
hadd merged/hist_WZ.root output/hist_WZ*.root
hadd merged/hist_ZZ.root output/hist_ZZ*.root
hadd merged/hist_LQcmutauLO.root output/hist_LQcmutauLO*.root
hadd merged/hist_LQctautauLO.root output/hist_LQctautauLO*.root
hadd merged/hist_LQcnunuLO.root output/hist_LQcnunuLO*.root
