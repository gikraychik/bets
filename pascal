program first;
var
	f1, f2, f3, f4: text;
	x, y, z, i, j, k: longint;
begin
assign(f1, 'scripts/filled');
reset(f1);
while (not eof(f1)) do begin
	readln(x);
	writeln('New: ', x);
end;
close(f1);
end.
