
-- compatibility script for restoring "old-style" getter/setter functions
-- only use this if you have a lot of existing scripts that you don't want to have to change

ags.getplayer = ags.get_player

local properties = {
  ViewFrame = {Flipped='g'; Frame='g'; Graphic='gs'; Loop='g'; Sound='gs'; Speed='g'; View='g'};
  DrawingSurface = {DrawingColor='gs'; Height='g'; UseHighResCoordinates='gs'; Width='g'};
  Room = {
    ColorDepth='!g'; Messages='!gi'; MusicOnLoad='!g';
    ObjectCount='!g';
    Width='!g';  Height='!g';
    BottomEdge='!g';  RightEdge='!g'; TopEdge='!g'; LeftEdge='!g';
  };
  Game = {
    CharacterCount='!g'; DialogCount='!g'; FileName='!g'; FontCount='!g';
    GlobalMessages='!gi'; GlobalStrings='!gsi'; GUICount='!g';
    InSkippableCutscene='!g'; InventoryItemCount='!g'; MinimumTextDisplayTimeMs='!gs';
    MouseCursorCount='!g'; Name='!gs'; NormalFont='!gs'; SkippingCutscene='!g';
    SpeechFont='!gs'; SpriteHeight='!gi'; SpriteWidth='!gi'; TextReadingSpeed='!gs';
    TranslationFilename='!g'; UseNativeCoordinates='!g'; ViewCount='!g';
  };
  Mouse = {Mode='!gs'; Visible='!gs'};
  File = {EOF='g'; Error='g'};
  InventoryItem = {CursorGraphic='gs'; Graphic='gs'; ID='g'; Name='gs'};
  Overlay = {Valid='g'; X='gs'; Y='gs'};
  DynamicSprite = {ColorDepth='g'; Graphic='g'; Height='g'; Width='g'};
  GUIControl = {
    AsButton='g'; AsInvWindow='g'; AsLabel='g'; AsListBox='g'; AsSlider='g'; AsTextBox='g';
    Clickable='gs'; Enabled='gs'; Height='gs'; ID='g'; OwningGUI='g'; Visible='gs';
    Width='gs'; X='gs'; Y='gs';
  };
  Label = {
    Font='gs'; Text='gs'; TextColor='gs';
    Clickable='gs'; Enabled='gs'; Height='gs'; ID='g'; OwningGUI='g'; Visible='gs';
    Width='gs'; X='gs'; Y='gs';
  };
  Button = {
    ClipImage='gs'; Font='gs'; Graphic='g';
    MouseOverGraphic='gs'; NormalGraphic='gs'; PushedGraphic='gs'; TextColor='gs';
    Text='gs';
    Clickable='gs'; Enabled='gs'; Height='gs'; ID='g'; OwningGUI='g'; Visible='gs';
    Width='gs'; X='gs'; Y='gs';
  };
  Slider = {
    BackgroundGraphic='gs'; HandleGraphic='gs'; HandleOffset='gs'; Max='gs'; Min='gs'; Value='gs';
    Clickable='gs'; Enabled='gs'; Height='gs'; ID='g'; OwningGUI='g'; Visible='gs';
    Width='gs'; X='gs'; Y='gs';
  };
  TextBox = {
    Font='gs'; Text='gs'; TextColor='gs';
    Clickable='gs'; Enabled='gs'; Height='gs'; ID='g'; OwningGUI='g'; Visible='gs';
    Width='gs'; X='gs'; Y='gs';
  };
  InvWindow = {
    CharacterToUse='gs'; ItemAtIndex='gi'; ItemCount='g';
    ItemHeight='gs'; ItemWidth='gs'; TopItem='gs'; ItemsPerRow='g'; RowCount='g';
    Clickable='gs'; Enabled='gs'; Height='gs'; ID='g'; OwningGUI='g'; Visible='gs';
    Width='gs'; X='gs'; Y='gs';
  };
  ListBox = {
    Font='gs'; HideBorder='gs'; HideScrollArrows='gs'; ItemCount='g'; Items='gsi'; RowCount='g';
    SaveGameSlots='gi'; SelectedIndex='gs'; TopItem='gs';
    Clickable='gs'; Enabled='gs'; Height='gs'; ID='g'; OwningGUI='g'; Visible='gs';
    Width='gs'; X='gs'; Y='gs';
  };
  GUI = {
    BackgroundGraphic='gs'; Clickable='gs'; Controls='gi'; ControlCount='g'; Height='gs'; ID='g';
    Transparency='gs'; Visible='gs'; Width='gs'; X='gs'; Y='gs'; ZOrder='gs';
  };
  Hotspot = {Enabled='gs'; ID='g'; Name='g'; WalkToX='g'; WalkToY='g'};
  Region = {
    Enabled='gs'; ID='g'; LightLevel='gs';
    TintEnabled='g'; TintBlue='g'; TintGreen='g'; TintBlue='g'; TintSaturation='g';
  };
  Dialog = {ID='g'; OptionCount='g'};
  DateTime = {Now='!g'; Year='g'; Month='g'; DayOfMonth='g'; Hour='g'; Minute='g'; Second='g'; RawTime='g'};
  --[[
  DialogOptionsRenderingInfo = {
    ActiveOptionID='gs'; DialogToRender='g'; Height='gs'; ParserTextBoxWidth='gs';
    ParserTextBoxX='gs'; ParserTextBoxY='gs'; Surface='g'; Width='gs'; X='gs'; Y='gs';
  };
  --]]
  System = {
    Gamma='!gs'; HardwareAcceleration='!g'; NumLock='!g'; OperatingSystem='!g';
    ScreenHeight='!g'; ScreenWidth='!g'; ScrollLock='!g'; SupportsGammaControl='!g';
    Version='!g'; ViewportWidth='!g'; ViewportHeight='!g'; VSync='!gs'; Windowed='!g';
  };
  Object = {
    Animating = 'g'; Baseline='gs'; BlockingHeight='gs'; BlockingWidth='gs'; Clickable='gs';
    Frame='g'; Graphic='gs'; ID='g'; IgnoreScaling='gs'; IgnoreWalkbehinds='gs'; Loop='g';
    Moving='g'; Name='g'; Solid='gs'; Transparency='gs'; View='g'; Visible='gs'; X='gs'; Y='gs';
  };
  Character = {
    ActiveInventory='gs'; Animating='g'; AnimationSpeed='gs'; Baseline='gs'; BlinkInterval='gs';
    BlinkView='gs'; BlinkWhileThinking='gs'; BlockingHeight='gs'; BlockingWidth='gs'; Clickable='gs';
    DiagonalLoops='gs'; Frame='gs'; HasExplicitTint='g'; ID='g'; IdleView='g'; IgnoreLighting='gs';
    IgnoreScaling='gs'; IgnoreWalkbehinds='gs'; InventoryQuantity='gsi'; Loop='gs'; ManualScaling='gs';
    MovementLinkedToAnimation='gs'; Moving='g'; Name='gs'; NormalView='g'; PreviousRoom='g'; Room='g';
    ScaleMoveSpeed='gs'; ScaleVolume='gs'; Scaling='gs'; Solid='gs'; Speaking='g'; SpeakingFrame='g';
    SpeechAnimationDelay='gs'; SpeechColor='gs'; SpeechView='gs'; ThinkView='gs';
    Transparency='gs'; TurnBeforeWalking='gs'; View='g'; WalkSpeedX='g'; WalkSpeedY='g';
    x='gs'; y='gs'; z='gs';
  };
}


local select = select

for objName, objProps in pairs(properties) do
  local obj = assert(ags[objName], 'object type not found: ' .. objName)
  for propName, propFlags in pairs(objProps) do
    local static = not not propFlags:match '!'
    local get = not not propFlags:match 'g'
    local set = not not propFlags:match 's'
    local array = not not propFlags:match 'i'
    assert(get, 'non-gettable properties not supported')
    local func
    if static then
      if array then
        local getter = assert(rawget(obj, 'geti_'..propName), objName..'.'..propName..'[] getter not found')
        if set then
          local setter = assert(rawget(obj, 'seti_'..propName), objName..'.'..propName..'[] setter not found')
          func = function(index, ...)
            if select('#', ...) == 0 then
              return getter(index)
            else
              return setter(index, (...))
            end
          end
        else -- get only
          assert(not rawget(obj, 'seti_'..propName), objName..'.'..propName..'[] setter exists but not flagged')
          func = function(index, ...)
            if select('#', ...) == 0 then
              return getter(index)
            else
              error('attempt to set '..objName..'.'..propName..'[] (a read-only property)',2)
            end
          end
        end
      else -- non array
        local getter = assert(rawget(obj, 'get_'..propName), objName..'.'..propName..' getter not found')
        if set then
          local setter = assert(rawget(obj, 'set_'..propName), objName..'.'..propName..' setter not found')
          func = function(...)
            if select('#', ...) == 0 then
              return getter()
            else
              return setter((...))
            end
          end
        else -- get only
          assert(not rawget(obj, 'set_'..propName), objName..'.'..propName..'[] setter exists but not flagged')
          func = function(self, index, ...)
            if select('#', ...) == 0 then
              return getter()
            else
              error('attempt to set '..objName..'.'..propName..' (a read-only property)',2)
            end
          end
        end
      end
    else -- not static
      if array then
        local getter = assert(rawget(obj, 'geti_'..propName), objName..'.'..propName..'[] getter not found')
        if set then
          local setter = assert(rawget(obj, 'seti_'..propName), objName..'.'..propName..'[] setter not found')
          func = function(self, index, ...)
            if select('#', ...) == 0 then
              return getter(self, index)
            else
              return setter(self, index, (...))
            end
          end
        else -- get only
          assert(not rawget(obj, 'seti_'..propName), objName..'.'..propName..'[] setter exists but not flagged')
          func = function(self, index, ...)
            if select('#', ...) == 0 then
              return getter(self, index)
            else
              error('attempt to set '..objName..'.'..propName..'[] (a read-only property)',2)
            end
          end
        end
      else -- non array
        local getter = assert(rawget(obj, 'get_'..propName), objName..'.'..propName..' getter not found')
        if set then
          local setter = assert(rawget(obj, 'set_'..propName), objName..'.'..propName..' setter not found')
          func = function(self, ...)
            if select('#', ...) == 0 then
              return getter(self)
            else
              return setter(self, (...))
            end
          end
        else -- get only
          assert(not rawget(obj, 'set_'..propName), objName..'.'..propName..' setter exists but not flagged')
          func = function(self, index, ...)
            if select('#', ...) == 0 then
              return getter(self)
            else
              error('attempt to set '..objName..'.'..propName..' (a read-only property)',2)
            end
          end
        end
      end
    end
    rawset(obj, propName, func)
  end
end
