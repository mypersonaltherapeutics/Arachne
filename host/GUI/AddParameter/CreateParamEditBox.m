function [hc, xPos] = CreateParamEditBox(value, xPos, desc)

    global panIdx params layout palette
    
    xPos = xPos + layout.xMargin2;
    parIdx = length(params{panIdx}) + 1;
    
    % Prepare tooltip
    if iscell(desc)
        desc = ['<html>', CellArray2HtmlString(desc), '</html>'];
    end
    
    hc = uicontrol('Style', 'edit', ...
                   'Units', 'pixels', ...
                   'Position', [xPos, 0, layout.ebWidth, layout.ebHeight], ...
                   'String', num2str(value), ...
                   'UserData', [panIdx, parIdx], ...
                   'BackgroundColor', palette.validColor, ...
                   'Callback', @generic_Callback, ...
                   'TooltipString', desc);
    xPos = xPos + layout.ebWidth;
    
end