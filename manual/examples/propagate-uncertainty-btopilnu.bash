eos-propagate-uncertainty \
    --kinematics s  0.00 --observable "B->pilnu::dBR/ds;l=e,form-factors=BCL2008,model=CKMScan" \
    --kinematics s  0.25 --observable "B->pilnu::dBR/ds;l=e,form-factors=BCL2008,model=CKMScan" \
    --kinematics s  0.50 --observable "B->pilnu::dBR/ds;l=e,form-factors=BCL2008,model=CKMScan" \
    --kinematics s  0.75 --observable "B->pilnu::dBR/ds;l=e,form-factors=BCL2008,model=CKMScan" \
    --kinematics s  1.00 --observable "B->pilnu::dBR/ds;l=e,form-factors=BCL2008,model=CKMScan" \
    --kinematics s  1.50 --observable "B->pilnu::dBR/ds;l=e,form-factors=BCL2008,model=CKMScan" \
    --kinematics s  2.00 --observable "B->pilnu::dBR/ds;l=e,form-factors=BCL2008,model=CKMScan" \
    --kinematics s  2.50 --observable "B->pilnu::dBR/ds;l=e,form-factors=BCL2008,model=CKMScan" \
    --kinematics s  3.00 --observable "B->pilnu::dBR/ds;l=e,form-factors=BCL2008,model=CKMScan" \
    --kinematics s  3.50 --observable "B->pilnu::dBR/ds;l=e,form-factors=BCL2008,model=CKMScan" \
    --kinematics s  4.00 --observable "B->pilnu::dBR/ds;l=e,form-factors=BCL2008,model=CKMScan" \
    --kinematics s  6.00 --observable "B->pilnu::dBR/ds;l=e,form-factors=BCL2008,model=CKMScan" \
    --kinematics s  7.00 --observable "B->pilnu::dBR/ds;l=e,form-factors=BCL2008,model=CKMScan" \
    --kinematics s  8.00 --observable "B->pilnu::dBR/ds;l=e,form-factors=BCL2008,model=CKMScan" \
    --kinematics s  9.00 --observable "B->pilnu::dBR/ds;l=e,form-factors=BCL2008,model=CKMScan" \
    --kinematics s 10.00 --observable "B->pilnu::dBR/ds;l=e,form-factors=BCL2008,model=CKMScan" \
    --kinematics s 11.00 --observable "B->pilnu::dBR/ds;l=e,form-factors=BCL2008,model=CKMScan" \
    --kinematics s 12.00 --observable "B->pilnu::dBR/ds;l=e,form-factors=BCL2008,model=CKMScan" \
    --pmc-input /tmp/pmc_monolithic_btopi+ff.hdf5 0 10000 \
    --pmc-sample-directory "/data/final/" \
    --output /tmp/unc_btopilnu.hdf5
