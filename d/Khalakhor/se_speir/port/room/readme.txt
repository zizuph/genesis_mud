GENERAL NOTES ON SEAN-RHIAN NPC'S
 
Named NPCs:
   Cimbaeth - cook who makes saltpeter of bird droppings for player (part of
              incense quest)
              "/d/Khalakhor/se_speir/port/room/kkitchen.c"
   Finegas  - instructor monk in the adv guild
              "/d/Khalakhor/se_speir/port/room/kclassrm.c"
   Gebann   - prior of kirk in Tabor Sagh; receives incense made in incense
              quest and gives his blessing so player can return to Semion for
              quest reward
              "/d/Khalakhor/se_speir/claryn/tabor/room/home_4.c"
   Mabon    - gardner in the kirk garden; gives hints for incense quest;
              wanders garden.
              "/d/Khalakhor/se_speir/port/room/kgarden6.c"
   Seandlar - Candle maker; must be present to buy candles
              "/d/Khalakhor/se_speir/port/room/kcandles.c"
   Semion   - Abbot of the main kirk; gives incense quest and rewards player;
              main point of info for players. (see semion_asks.inc)
              "/d/Khalakhor/se_speir/port/room/koffice.c"
 
General NPCs:
   kmonk    - general kirk monk, wanders kirk
              "/d/Khalakhor/se_speir/port/room/k*.c"
              "/d/Khalakhor/se_speir/claryn/tabor/room/kirk*.c"
   knovice  - general kirk novice, wanders kirk
              "/d/Khalakhor/se_speir/port/room/k*.c"
 
Support code:
   monkbase.c        - base code inherited by all monks/novices
   monk_specatck.c   - special attack code inherited by monks
   nov_specatck.c    - special attack code inherited by novices
   spintro.c         - introduce code for speaking monks
   vowintro.c        - introduce code for monks with vow of silence
   teamsupt.inc      - copied from Calia/Argos, code for getting assistance
                       from other monks when attacked. Included by monkbase.c
