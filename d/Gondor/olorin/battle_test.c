inherit "/d/Gondor/common/room";

string exa_sign()
{
     return "A sign, stupid.\n";
}

create_room() 
{
  set_short("The Battle Room");
  set_long("This is the battle room. You wonder why there are no exits here.\n");
    add_item("sign", "@@exa_sign@@");
}

