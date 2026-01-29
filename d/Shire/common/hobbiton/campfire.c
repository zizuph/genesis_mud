/*
 *  The campfire in the middle of the plain
 *  Tricky 3-3-91
 */

init() {
   add_action("party","light",0);
   add_action("party","burn",0);
}

reset(arg) {
   if(arg)
      return;
}

id(str) {
   return (str == "fire" || str == "camp fire" || str == "campfire");
}

short() {
   return "an extinguished campfire";
}

long() {
   write("The campfire is used by the hobbits on their picnic parties.\n");
   return;
}

get() {
   return 0;
}

query_weight() {
   return 0;
}

party(str) {
   if (id(str)) {
      write("You light the fire and sit next to it.\n");
      write("Suddenly, some hobbits join you near the fire. They\n");
      write("have brought their picnic baskets and offer you some\n");
      write("food. The food tastes quite good and while you eat it,\n");
      write("the hobbits invite you to come and visit them in Hobbiton,\n");
      write("the nearby hobbit village. When the campfire is almost\n");
      write("gone and the food is all eaten, the hobbits return to\n");
      write("their homes, northwest from here.\n");
      if (random(10) < 1)
         this_player()->heal_self(10);
      return 1;
   }
   return 0;
}
