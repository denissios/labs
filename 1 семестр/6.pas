program Project1;

type
point = ^tel;
    tel = record
        surname : string[25];
        number : string[12];
        adress : string [50];шщз
        next : point;
    end;
    
  var P,Q,First: point;
  file1:text;
  s : tel;
 
 
procedure ReadList;
var 
count, i : integer;
  begin
   readln(count); 
   assign(file1, 'information.txt');
   rewrite(file1);
   for i := 1 to count do
   begin   
      readln(s.surname);
      readln(s.number);
      readln(s.adress);
      writeln();
      write(file1, s);
   end;   
  end;
  
  
procedure DeleteUser; 
var surn:string[25];
  begin
   writeln('Which user must be deleted?');
   readln(surn);
   P:= First;
   First:=nil;
     while P<>nil do 
       begin
          if surn<>p^.surname then
            begin
               new(Q);
               Q^.surname:=p^.surname;
               Q^.number:=p^.number;
               Q^.adress:=p^.adress;
               Q^.next:=First;
               First:=Q;
            end;
         P:= P^.next;
       end;
   writeln;
  end;
  
  
procedure PrintList;
var probel,surn,num,adr:string;
  begin
   probel:=' ';
   writeln('List:');
   Q:=First;
    while Q<>nil do 
      begin
        surn:=Q^.surname;
        num:=Q^.number;
        adr:=Q^.adress;
        if length(surn)<15 then
          repeat
            surn:=surn+probel;
          until length(surn)=15;
        if length(num)<12 then
          repeat
            num:=num+probel;
          until length(num)=12;
        writeln(surn,'   ',num,'    ',adr);
        Q:= Q^.next;
      end;
    writeln;
  end;
  
  
procedure ChangeData;
 var surn: string[25];
 begin
  Writeln('Surname of user,whose data must be changed: ');
  readln(surn);
  Q:=First;
   while Q<>nil do 
      begin
        if q^.surname=surn then
          begin
             write('New number: ');
             readln(q^.number);
             write('New adress: ');
             readln(q^.adress);
          end;
        Q:= Q^.next;
     end;
 end;
 
 
procedure AddUser;
  begin
    while(p^.next <> nil)
      p := p^.next;
    writeln('Enter new users data');
    new(Q);
    write('surname: ');
    readln(Q^.surname);
    write('number: ');
    readln(Q^.number);
    write('adress: ');
    readln(Q^.adress);
    Q^.next:=First;
    First:=Q;
  end;
  
  
begin
ReadList;
DeleteUser;
AddUser;
ChangeData;
PrintList;
end.