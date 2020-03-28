program Project1;

type
    point = ^information;
    
    information = record
        surname : string[25];
        mark1 : integer;
        mark2 : integer;
        next : point;
end;
    
var 
  P, First : point;
  file1 : text;
  s : information;

 
procedure ReadList;
var 
count, i : integer;
begin
   write('Enter the count of students: ');
   readln(count); 
   assign(file1, 'information.txt');
   rewrite(file1);
   for i := 1 to count do
   begin
      P := First;
    while(P <> nil) do
      P := P^.next;
    writeln('Enter new student');
    new(P);
    write('surname: ');
    readln(P^.surname);
    write('mark1: ');
    readln(P^.mark1);
    write('mark2: ');
    readln(P^.mark2);
   end;   
end;
  
  
procedure Sort;
var surn : string;
begin
   writeln('Otlichniki: ');
   P := First;
   surn := s.surname;
   writeln(surn);
   while P <> nil do 
   begin
    // if ((P^.mark1 = 5) and (P^.mark2 = 5)) then
       writeln(P^);
     P := P^.next;
   end;
   
   writeln('Neyspevauzhie: ');
   P:= First;
   while P <> nil do 
   begin
     writeln(P^.surname);
     if ((P^.mark1 = 2) and (P^.mark2 = 2)) then
       writeln(P^.surname);
     P := P^.next;
   end;
   
   writeln('Others: ');
   P := First;
   while P <> nil do 
   begin
     if (((P^.mark1 <> 2) or (P^.mark2 <> 2)) and ((P^.mark1 <> 5) or (P^.mark2 <> 5))) then
       writeln(P^.surname);
     P := P^.next;
   end;
   writeln();
end;
  
 
procedure AddUser;
begin
    P := First;
    while(P <> nil) do
      P := P^.next;
    writeln('Enter new student');
    new(P);
    write('surname: ');
    readln(P^.surname);
    write('mark1: ');
    readln(P^.mark1);
    write('mark2: ');
    readln(P^.mark2);
end;
  
  
begin
ReadList;
Sort;
AddUser;
Sort;
end.