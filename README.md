# ![logo](https://raw.githubusercontent.com/azerothcore/azerothcore.github.io/master/images/logo-github.png) AzerothCore Module: mod-direbrew-anti-block

[![AzerothCore Module](https://img.shields.io/badge/AzerothCore-Module-red?style=flat-square&logo=github)](https://github.com/azerothcore/azerothcore-wotlk)
[![C++20](https://img.shields.io/badge/Language-C++20-00599C?style=flat-square&logo=c%2B%2B)](https://isocpp.org/)
[![Branch 3.3.5a](https://img.shields.io/badge/Branch-3.3.5a-orange?style=flat-square)](https://github.com/azerothcore/azerothcore-wotlk)
[![License GPL-2.0-or-later](https://img.shields.io/badge/License-GPL--2.0--or--later-blue?style=flat-square)](LICENSE)
[![GitHub Stars](https://img.shields.io/github/stars/AlsoNotMehh/mod-direbrew-anti-block?style=flat-square&color=yellow&logo=github)](https://github.com/AlsoNotMehh/mod-direbrew-anti-block/stargazers)

AzerothCore WotLK module intended to prevent the Personal Mole Machine summoned
by Direbrew's Remote from blocking doorways in capitals and sanctuaries.

Use this module if players are placing mole machines in narrow entrances to block
other players. It moves the proposed fix into an optional module, following the
discussion on the original PR. Verified retail behavior is not claimed.

## Sources

- [Issue #27857: Direbrew remote](https://github.com/azerothcore/azerothcore-wotlk/issues/27857)
  — original problem report and video evidence.
- [PR #27858: Prevent door blocking](https://github.com/azerothcore/azerothcore-wotlk/pull/27858)
  — original implementation by AlsoNotMehh and the discussion about making it a module.
- [Original code change](https://github.com/azerothcore/azerothcore-wotlk/commit/4e6e64b48dc47c537182a63f433c1b2100ca060d)
  — the implementation extracted into this repository.

## Behavior

- Applies only to Personal Mole Machine (gameobject 190022), summoned using item 37863.
- Preserves the stock one-time `GO_STATE_READY` initialization.
- Disables server collision when the object's area or zone has the capital or sanctuary flag.
- Retains stock collision elsewhere, including when neither area record is available.

## Install

1. From your AzerothCore directory, run:
   ```sh
   git clone https://github.com/AlsoNotMehh/mod-direbrew-anti-block.git modules/mod-direbrew-anti-block
   ```
   Keep that folder name: AzerothCore derives the loader function from it.
2. Back up the world database, particularly any custom script binding and
   `smart_scripts` rows for gameobject 190022. This module replaces that object's AI.
3. Re-run your normal AzerothCore CMake configuration with modules enabled, then
   build and install worldserver. The current module system discovers the C++ source
   and `Addmod_direbrew_anti_blockScripts()` automatically.
4. With worldserver stopped, apply `data/sql/db-world/base/00_direbrew_anti_block.sql`
   to your world database. If your module SQL updater already applied it, no manual
   import is needed. The SQL is safe to apply repeatedly.
5. Start worldserver and verify there are no missing-script errors.

No core source patch is required. If you previously applied PR #27858, revert its
C++ changes before using this module; the module SQL replaces its database binding.

## Remove

Stop worldserver. Remove the module directory, reconfigure, rebuild and install.
Restore your backed-up AI binding and SmartAI rows. For a stock installation,
`sql/uninstall.sql` restores the upstream SmartAI behavior. Do not use that stock
rollback to restore custom scripts. Restart worldserver after the database is restored.

## In-game verification

1. Use `.additem 37863` and summon the machine in a narrow Stormwind doorway.
2. With a second player, verify passage in both directions and normal machine use.
3. Repeat in a flagged sanctuary such as Shattrath and in a capital subarea.
4. Summon it in an ordinary outdoor area and compare collision and use with stock.
5. Repeat summoning and allow the machine to expire; check for errors.
6. Remove the module using the steps above and verify stock behavior returns.

## Validation and limits

Source and loader signatures were checked against AzerothCore commit
`0781768d0ed1c75de7eb4ec14f03087e71fa9989`. The original PR's behavior is preserved.
Compilation and live client/server testing have not been performed.
`EnableCollision(false)` changes server collision; client traversal still needs
in-game verification. The location policy runs once on the first AI update.
Later object state changes or relocation are not handled. Sanctuary protection
uses DBC flags; locations recognized only by special map rules are not included.

## ⭐ Show your support

If this module is useful for your server, consider giving it a star on GitHub.

## 👤 Credits

- **Author:** [AlsoNotMehh](https://github.com/AlsoNotMehh) ([Discord](https://discord.com/users/1063304041419001966) / [Email](mailto:itsbrayanrodriguez@gmail.com))
- **Framework:** [AzerothCore](https://www.azerothcore.org)
- **Original implementation:** [AzerothCore PR #27858](https://github.com/azerothcore/azerothcore-wotlk/pull/27858) by AlsoNotMehh. See [Sources](#sources) and [AUTHORS](AUTHORS).
- **AI assistance:** Module extraction and documentation were prepared with OpenAI Codex.

## 📄 License

This project is licensed under [GPL-2.0-or-later](LICENSE).
