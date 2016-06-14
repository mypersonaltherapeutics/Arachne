@echo off

call vars.bat

set "MPIDIR=C:\Program Files\Microsoft Compute Cluster Pack"

set MPIINCLDIR="%MPIDIR%\Include"
set MPILIBDIR="%MPIDIR%\Lib\amd64"
set TARGETNAME=gs

echo on

del %TARGETNAME%.*

cl /openmp /O2 /Oi /Ot /GL /EHsc /I %MLINCLDIR% /I %MPIINCLDIR% /I %GSINCLDIR% /Fe%TARGETNAME% main.cpp GammaSimulator.cpp DistEnv.cpp DistributionWrapper.cpp BoostedBernoulliDistribution.cpp %MATFILEIO%\MatFileIOUtils.cpp MathUtils.cpp OtherFileIOUtils.cpp %CONTAINERS%\LocalVector.cpp %CONTAINERS%\DistVector.cpp %CONTAINERS%\LocalDenseMatrix.cpp %CONTAINERS%\LocalSparseMatrix.cpp %CONTAINERS%\DistDenseMatrix.cpp %CONTAINERS%\DistSparseMatrix.cpp %SCMs%\SCMFactory.cpp %SCMs%\SCMBase.cpp %SCMs%\SimpleSCM.cpp %SCMs%\SparseSCM.cpp %SCMs%\ZeroSCM.cpp %SCMs%\UniformSCM.cpp %SCMs%\OneBitSCM.cpp %SCMs%\InPlaceSCM.cpp %ASTRO%\AstroNet.cpp %GABA%\GABA.cpp %STDP%\AnalyticStdpMechanism.cpp %STDP%\TabulatedStdpMechanism.cpp %STDP%\BaseStdpMechanism.cpp %XCUR%\ExtraCurrent.cpp %MLLIBDIR%\libmat.lib %MLLIBDIR%\libmx.lib %MPILIBDIR%\msmpi.lib

del *.obj

pause