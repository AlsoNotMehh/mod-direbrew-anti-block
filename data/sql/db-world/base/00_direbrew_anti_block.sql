-- Personal Mole Machine summoned by Direbrew's Remote.
-- Back up any custom AI binding and SmartAI rows before installing.
UPDATE `gameobject_template` SET `AIName` = '', `ScriptName` = 'go_mod_direbrew_anti_block' WHERE `entry` = 190022;

DELETE FROM `smart_scripts` WHERE `entryorguid` = 190022 AND `source_type` = 1;
