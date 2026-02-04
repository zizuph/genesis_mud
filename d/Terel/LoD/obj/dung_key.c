inherit "/std/key";

int num=0;

public void
create_key()
{
    ::create_key();

    set_name("key");
    set_adj("large");
    add_adj("iron");
    set_long("A large iron key.@@my_num@@\n");
}

public void
set_key(int n)
{
    ::set_key(n);
    
    num = n - 13500;
    if (num < 1 || num > 7) num = 0;
    
    if (num)
        add_name("key " + num);
}

public string
my_num()
{
    if (!num)
        return "";
        
    return " It has a small number engraved on it: " + num + ".";
}
