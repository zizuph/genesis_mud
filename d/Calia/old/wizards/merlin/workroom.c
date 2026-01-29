inherit "/std/workroom"; 
 
#define PAGE    100 
 
int size; 
string file; 
 
create_workroom() 
{ 
 
  set_short("Merlin's workroom"); 
  set_long("This is Merlins's hidden cave.  White light shines comes from\n" 
    + "everywhere. You can also see a small fire.\n"); 
 
  add_exit("/d/Genesis/wiz/entrance",                       "news", 0); 
  add_exit("/d/Genesis/wiz/domain",                         "domain", 0); 
  add_exit("/d/Genesis/wiz/idea",                           "idea", 0); 
  add_exit("/d/Genesis/wiz/post",                           "post", 0); 
  add_exit("/d/Genesis/wiz/discuss",                        "discuss", 0); 
  add_exit("/d/Genesis/wiz/lpc",                            "lpc", 0); 
  add_exit("/d/Genesis/wiz/infotool",                       "tool", 0); 
  add_exit("/d/Genesis/wiz/admin",                          "admin", 0); 
  add_exit("/d/Calia/workroom",                            "meet", 0); 
  add_exit("/d/Calia/glykron/palace/guild",                "guild", 0); 
  add_exit("/d/Calia/merlin/gelan/rooms/drawbridge",              "gelan", 0); 
  add_exit("/d/Calia/merlin/gelan/rooms/square_northend_center_e","square", 0); 
 
} 
 
init() 
{ 
 
    add_action("type","type"); 
    add_action("test","test"); 
    ::init(); 
 
} 
 
int 
type(string arg) 
{ 
 
    string *argv; 
    string error; 
 
    if(!strlen(arg)) 
    { 
        notify_fail("What do you want to type ?\n"); 
        return 0; 
    } 
 
    argv = explode(arg, " "); 
 
    if(sizeof(argv) > 1) 
        error = ", ignoring rest of line.\n"; 
    else 
        error = ".\n"; 
 
    size = file_size(argv[0]); 
 
    if(size == -1) 
    { 
        notify_fail("&&&File not found" + error); 
        return 0; 
    } 
 
    if(size == -2) 
    { 
        notify_fail("&&&File is a directory" + error); 
        return 0; 
    } 
 
    tell_object(this_player(),"*#*"); 
 
    file = argv[0]; 
 
    input_to("type2",1); 
 
    return 1; 
} 
 
 
type2(string str) 
{ 
 
    int i; 
    string result; 
 
    for(i = 0; ; i++) 
    { 
        result = read_file(file, i * PAGE, (i + 1) * PAGE - 1); 
        if(!result) 
            break; 
        tell_object(this_player(), result); 
    } 
 
 
    tell_object(this_player(),"*#* OK, typing over, you should have " + size + " Bytes.\n"); 
 
} 
 
int 
test(string arg) 
{ 
    object cn; 
 
    add_action("query_race","init"); 
 
    return 1; 
} 
