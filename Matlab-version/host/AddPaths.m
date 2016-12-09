function AddPaths()
%% Add paths of all the m-files to the Matlab search path

    addpath(genpath(cd));
    
    rmpath(fullfile(cd, 'Core', '3rdparty'));
    rmpath(fullfile(cd, 'Core', 'ModFileUtils', 'CppCodeTemplates'));
    rmpath(genpath(fullfile(cd, 'Core', 'scripts')));
    
end