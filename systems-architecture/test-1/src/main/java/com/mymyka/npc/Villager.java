package com.mymyka.npc;

import com.mymyka.player.Player;

public class Villager implements NPC {
    private String name;

    public Villager(String name) {
        this.name = name;
    }

    @Override
    public void sayHello(Player player) {
        System.out.println("Villager(" + name + "): Hello ! " + player.getName());
    }
}
