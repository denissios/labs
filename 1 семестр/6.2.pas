program Lab6;

type
    int = integer;
    Node = record
        surname :string;
        mark1 : int;
        mark2 : int;
        next : ^Node;
    end;

procedure delete(var head : ^Node);
var
    ptr : ^Node;
begin
    ptr := head;
    while ptr <> nil do
    begin
        ptr := head^.next;
        Dispose(head);
        head := ptr;
    end;
end;

procedure add(var head : ^Node; val : Node);
var
    node : ^Node;
begin
    node := head;
    if head = nil then
    begin
        New(head);
        node := head;
    end
    else
        while node^.next <> nil do
            node := node^.next;
       
    New(node^.next);
    node^.surname := val.surname;
    node^.mark1 := val.mark1;
    node^.mark2 := val.mark2;
end;

procedure print(var head : ^Node);
var
    ptr : ^Node;
begin
    ptr := head;
    if ptr = nil then
        Write('List is empty')
    else
    begin
        while ptr^.next <> nil do
        begin
            WriteLn(ptr^.surname, ' ', ptr^.mark1, ptr^.mark2);

            ptr := ptr^.next;
        end;
    end;
    Write(#10);
end;

var
    input : text;
    otl, dvo, oth, all : ^Node;
    n : Node;
    line : string;

begin
    Assign(input, 'information2.txt');
    Reset(input);
    while not eof(input) do
    begin
        ReadLn(input, line);
        var tokens := line.Split(' ');
        
        n.surname := tokens[0];
        n.mark1 := StrToInt(tokens[1]);
        n.mark2 := StrToInt(tokens[2]);
        
        add(all, n);
        if (n.mark1 = 5) or (n.mark2 = 5) then
            add(otl, n)
        else if (n.mark1 = 2) or (n.mark2 = 2) then
            add(dvo, n)
        else
            add(oth, n);
    end;
    CloseFile(input);
    
    WriteLn('All'); print(all);
    WriteLn('Otl'); print(otl);
    WriteLn('Dvo'); print(dvo);
    WriteLn('Oth'); print(oth);
    
    delete(all);
    delete(otl);
    delete(dvo);
    delete(oth);
end.