program abc;

var 
  z, x, y1, y2 : real;
  k : integer;
  s : string; 
  
begin
while(true) do
begin
  write('Enter x: ');
  readln(x);
  write('Enter number accuracy: ');
  readln(z);
  
  k := 1;
  y1 := power((-1), k)*(power(x, k)/(k*power(2, k)));
  
  while(true) do
  begin
    k := k + 1;
    y2 := y1 + power((-1), k)*(power(x, k)/(k*power(2, k)));
    if(abs(abs(y2) - abs(y1)) < 1 / power(10, z)) then
    begin
      write('Sum: ');
      writeln(y1);
      break;
    end;
      
    k := k + 1;
    y1 := y2 + power((-1), k)*(power(x, k)/(k*power(2, k)));
    if(abs(abs(y2) - abs(y1)) < 1 / power(10, z)) then
    begin
      write('Sum: ');
      writeln(y2);
      break;
    end;
  end;
  write('Do you want to continue? ');
  readln(s);
  if((s = 'NO') or (s = 'No') or (s = 'no')) then
    break;
  writeln();
end;
end.
