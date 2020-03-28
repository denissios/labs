program abc;

var arr : array[1..100] of string;

procedure _quick_sort(a, b : integer);
var
  m, k : integer;
  c, buf : string;
begin
  m := a;
  k := b;
  c := arr[(m+k) div 2];
  repeat
    while arr[m] < c do inc(m);
    while arr[k] > c do dec(k);
    if m <= k then
    begin
      buf := arr[m];
      arr[m] := arr[k];
      arr[k] := buf;
      inc(m);
      dec(k);
    end;
  until m > k;
  if a < k then _quick_sort(a, k);
  if m < b then _quick_sort(m, b);
end;

type
  information = record
  surname : string[20];
  marka : string[20];
  nomer : string[10];
  location : integer;
end;

var
  s : information;
  f : file of information;
  count : integer;
  i, j : integer;
  mar : string;
  
begin
  assign(f, 'information.txt');

  rewrite(f);
  writeln('Enter the count of car owners');
  readln(count);
  for i := 1 to count do
  begin
    write('Enter the surname of ', i, ' owner: ');
    readln(s.surname);
    write('Enter marka of car: ');
    readln(s.marka);
    write('Enter registration number: ');
    readln(s.nomer);
    write('Enter the location in garage: ');
    readln(s.location);
    writeln();
    write(f, s);
  end;
  close(f);

  reset(f);
  writeln('Enter marka of car: ');
  readln(mar);
  writeln;
  i := 1;
  while not EOF(f) do
  begin
    read(f, s);
    if s.marka = mar then
    begin
      arr[i] := s.surname; 
      inc(i);
    end;
  end;
  close(f);
 
  _quick_sort(1, i - 1);
 
  i := 1;
  for j := 1 to count do
  begin
    reset(f);
    while not EOF(f) do
    begin
      read(f, s);
      if s.surname = arr[i] then
      begin
        writeln(s.surname, ' ', s.marka, ' ', s.nomer, ' ', s.location);
        inc(i);
      end;
    end;
  end;
end.