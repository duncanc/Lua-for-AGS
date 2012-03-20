using System;
using System.Collections.Generic;
using System.Text;
using AGS.Types;

namespace AGS.Plugin.Lua
{
    public static class HacksAndKludges
    {
        private static IEnumerable<string> YieldAudioClipScriptNames(AudioClipFolder folder)
        {
            foreach (AudioClip clip in folder.Items)
            {
                yield return clip.ScriptName;
            }
            foreach (AudioClipFolder subfolder in folder.SubFolders)
            {
                foreach (string scriptname in YieldAudioClipScriptNames(subfolder))
                {
                    yield return scriptname;
                }
            }
        }

        public static IEnumerable<string> YieldAudioClipScriptNames(IGame game)
        {
            Game typedGame = (Game)game;
            return YieldAudioClipScriptNames(typedGame.RootAudioClipFolder);
        }
    }
}
