package com.mymyka.npc;

public abstract class NPC {
    private String name;

    public NPC(String name) {
        this.name = name;
    }

    public NPC() {}

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public void spawn() {
        System.out.println(name + " spawned !");
    }
}
