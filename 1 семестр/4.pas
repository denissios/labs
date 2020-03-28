program abc;

function column(var a: array of array of integer; var M : integer) : integer;
  begin
      write('In column: ');
      var count, k, z : integer;
      count := 0;
      for k := 0 to M - 1 do
      begin
        for z := 0 to M - 1 do
          if(a[z][k] = 1) then
            count := count + 1;
        write(count);
        write(' ');
        count := 0;
      end;
      writeln();
  end;
  
function line(var a: array of array of integer; var M : integer) : integer;
  begin
      write('In line: ');
      var count, k, z : integer;
      count := 0;
      for k := 0 to M - 1 do
      begin
        for z := 0 to M - 1 do
          if(a[k][z] = 1) then
            count := count + 1;
        write(count);
        write(' ');
        count := 0;
      end;
      writeln();
  end;  
  
var
  N, i, j : integer;
  matrix : array of array of integer;
  f : string;
  
begin
  while(true) do
  begin
    readln(N);
    SetLength(matrix, N);
    for i := 0 to N - 1 do
      SetLength(matrix[i], N);
      
    for i := 0 to N - 1 do
      for j := 0 to N - 1 do
        read(matrix[i][j]);
    
    column(matrix, N);
    line(matrix, N);
    
    write('Do you want to continue?');
    readln(f);
    if((f = 'NO') or (f = 'No') or (f = 'no')) then
      break;
    writeln();
  end;
end.