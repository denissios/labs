program abc;

var
  i, j, b, count, count1, number : integer;
  f, s, s1, s2 : string;
  a : array of integer;
  
begin
  while(true) do
  begin
    readln(s);
    count := 0;
    s1 := ' ';
    s := s + s1;  
    s2 := s;
    while((length(s2) <> 0) and (s2 <> ' ')) do
    begin
      number := pos(' ', s2);
      count := count + 1;
      delete(s2, 1, number);
    end;
    
    SetLength(a, count);
    count := 0;
 
    while((length(s) <> 0) and (s <> ' ')) do
    begin
      number := pos(' ', s);   
      a[count] := number - 1;
      count := count + 1;
      delete(s, 1, number);
    end;
    
    for i := 0 to count - 1 do
      for j := 0 to count - 2 do
        if(a[j + 1] < a[j]) then
        begin
          b := a[j];
          a[j] := a[j + 1];
          a[j + 1] := b;
        end;
        
    count1 := 1;  
    b := a[0];
    for i := 0 to count - 1 do
      if((i = 0) or (a[i] <> b)) then
      begin
       for j := 0 to count - 1 do
         if((j <> i) and (a[i] = a[j])) then
           count1 := count1 + 1;
       write('Number of words with ');
       write(a[i]);
       write(' letters: ');
       writeln(count1);
       count1 := 1;
       b := a[i];
      end;
    
    write('Do you want to continue?');
    writeln();
    readln(f);
    if((f = 'NO') or (f = 'No') or (f = 'no')) then
      break;
    writeln();
  end;
end.