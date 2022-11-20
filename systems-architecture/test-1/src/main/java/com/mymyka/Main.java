package com.mymyka;

import com.mymyka.npc.NPC;
import com.mymyka.npc.NPCDecorator;
import com.mymyka.npc.TradableNPCDecorator;
import com.mymyka.npc.Villager;
import com.mymyka.player.Builder;
import com.mymyka.player.Player;

public class Main {
    public static void main(String[] args) {
        Player playerSteve = new Builder("Steve");
        NPC npcBob = new Villager("Bob");
        npcBob.sayHello(playerSteve);

        // Some game events that makes NPC Bob tradable

        NPCDecorator tradableNPCBob = new TradableNPCDecorator(npcBob);
        tradableNPCBob.sayHello(playerSteve);
    }
}