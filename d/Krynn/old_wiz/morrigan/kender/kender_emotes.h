/*-------------------------==< klook >==-------------------------*/
int
klook(string str)
{
   
   object *oblist;
   
   if (!str)
      {
      write("You look around, wide-eyed with curiousity.\n");
      say(QCTNAME(TP)+" looks around, wide-eyed with curiousity.\n");
      return 1;
   }
   
   oblist = parse_this(str, "[at] [the] %l");
   
   if (!sizeof(oblist))
      {
      NF("Look at whom?\n");
      return 0;
   }
   
   actor("You look at", oblist, ", wide-eyed with curiousity.");
   targetbb(" looks at you, wide-eyed with curiousity.", oblist);
   all2actbb("  looks at", oblist, ", wide-eyed with curiousity.");
   return 1;
}
