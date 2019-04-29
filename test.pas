procedure solve(dep:integer);
var i:integer;
begin
    if dep=n+1 then
        begin
            writeln(s);
            exit;
        end;
    for i:=1 to n do
        if not used[i] then
            begin
                s:=s+chr(i+ord('0'));
                used[i]:=true;
                solve(dep+1);
                s:=copy(s,1,length(s)-1);
                used[i]:=false;
            end;
end;