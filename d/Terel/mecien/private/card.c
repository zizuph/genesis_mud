inherit "/std/object";


init(){
add_action("read", "read");
add_action("charge", "charge");
::init();
}

read(string str){
if(!str) return 0;
if(str == "card"){
this_player()->catch_msg("Gold Master's Express Card\n" +
"\n Levels may be charged upon Keepersave account.\n"
+ " Never leave your domain without it.\n"
);
return 1;
}
}

charge(string str){
if(!str){
write("Charge what?\n");
return 1;
}
if(str == "level"){
this_player()->catch_msg("You do not have sufficient credit!\n");
return 1;
}
}

create_object(){
set_name("card");
set_adj("little");
add_adj("gold");
set_long("Its a beautiful gold card, small enough for a pocket.\n");

set_long("It is a small gold card, with writing on it. It could\n" +
"easily fit in a pocket.\n");

}
