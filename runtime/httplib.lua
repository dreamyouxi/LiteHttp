
function packCustomHtmlData(msg)
	return "<html lang='en'><head><meta charset='utf-8'></head><body><p>" .. msg .."</p></body></html>";
end


function skipWhite(str)
	local s,num = string.gsub(str, " ", "");
	local s,num=string.gsub(s, "+", "");
--	local s2,num=string.gsub(s1, "%20", "");
	
	return s;
end

