package 
{
	import flash.display.Bitmap;
	import flash.display.BitmapData;
	import flash.display.Graphics;
	import flash.display.SimpleButton;
	import flash.display.Sprite;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.events.TimerEvent;
	import flash.geom.Rectangle;
	import flash.media.Sound;
	import flash.media.SoundMixer;
	import flash.net.FileFilter;
	import flash.net.FileReference;
	import flash.system.Security;
	import flash.system.SecurityDomain;
	import flash.text.TextFieldAutoSize;
	import flash.utils.ByteArray;
	import flash.utils.Timer;
	
	// MinimalComps GUI Library
	import com.bit101.components.*;
	
	// Game-Music-Emu Wrapper Classes
	import gme.EmulatorType;
	import gme.GameMusicEmu;
	import gme.SampleRate;
	
	/**
	 * game music emu sample.
	 * @author Hikipuro
	 */
	public class Main extends Sprite 
	{
		/**
		 * game music emu.
		 */
		private var gameMusicEmu:GameMusicEmu;
		
		/**
		 * label for music infomation.
		 */
		private var labelInfo:Label;
		
		/**
		 * label for current position.
		 */
		private var labelPosition:Label;
		
		/**
		 * label for music length.
		 */
		private var labelLength:Label;
		
		/**
		 * current player position.
		 */
		private var sliderPosition:HSlider;
		
		/**
		 * sliderPosition is seeking.
		 */
		private var sliderSeeking:Boolean;
		
		/**
		 * to get curernt player position.
		 */
		private var timer:Timer;
		
		private var checkSpectrum:CheckBox;
		
		private var count:uint = 0;
		private var bitmap:Bitmap;
		
		/**
		 * constructor.
		 */
		public function Main():void 
		{
			if (stage) init();
			else addEventListener(Event.ADDED_TO_STAGE, init);
		}
		
		/**
		 * initialize method.
		 * @param	e
		 */
		private function init(e:Event = null):void 
		{
			removeEventListener(Event.ADDED_TO_STAGE, init);
			// entry point
			
			var bitmapData:BitmapData = new BitmapData(128, 112);
			bitmap = new Bitmap(bitmapData);
			bitmap.x = 130;
			bitmap.y = 70;
			addChild(bitmap);
			
			// create "Play" button
			var nsfButton:PushButton;
			nsfButton = new PushButton(this, 10, 10, "Play NSF", function (e:Event):void 
			{
				if ( gameMusicEmu.isPlaying ) {
					gameMusicEmu.stop();
				}
				gameMusicEmu.init(EmulatorType.NSF);
				gameMusicEmu.load("Super Mario Bros. 1.nsf");
				
				// set tempo, double speed
				//gameMusicEmu.setTempo(2);
			});
			nsfButton.visible = true;
			
			var vgmButton:PushButton;
			vgmButton = new PushButton(this, 10, 40, "Play VGM", function (e:Event):void 
			{
				if ( gameMusicEmu.isPlaying ) {
					gameMusicEmu.stop();
				}
				gameMusicEmu.init(EmulatorType.VGM);
				gameMusicEmu.load("02 Green Hill Zone.vgm");
			});
			vgmButton.visible = true;
			var spcButton:PushButton;
			spcButton = new PushButton(this, 10, 70, "Play SPC", function (e:Event):void 
			{
				if ( gameMusicEmu.isPlaying ) {
					gameMusicEmu.stop();
				}
				gameMusicEmu.init(EmulatorType.SPC);
				gameMusicEmu.load("sbm5-06a.spc");
			});
			spcButton.visible = true;
			
			var hesButton:PushButton;
			hesButton = new PushButton(this, 10, 100, "Play HES", function (e:Event):void 
			{
				if ( gameMusicEmu.isPlaying ) {
					gameMusicEmu.stop();
				}
				gameMusicEmu.init(EmulatorType.HES);
				gameMusicEmu.load("After Burner 2.hes");
			});
			hesButton.visible = true;
			
			var gbsButton:PushButton;
			gbsButton = new PushButton(this, 10, 130, "Play GBS", function (e:Event):void 
			{
				if ( gameMusicEmu.isPlaying ) {
					gameMusicEmu.stop();
				}
				gameMusicEmu.init(EmulatorType.GBS);
				gameMusicEmu.load("Tetris.gbs");
			});
			gbsButton.visible = true;
			
			var kssButton:PushButton;
			kssButton = new PushButton(this, 10, 160, "Play KSS", function (e:Event):void 
			{
				if ( gameMusicEmu.isPlaying ) {
					gameMusicEmu.stop();
				}
				gameMusicEmu.init(EmulatorType.KSS);
				gameMusicEmu.load("gradius2.kss");
			});
			kssButton.visible = true;
			
			var vgzButton:PushButton;
			vgzButton = new PushButton(this, 10, 190, "Play VGZ", function (e:Event):void 
			{
				if ( gameMusicEmu.isPlaying ) {
					gameMusicEmu.stop();
				}
				gameMusicEmu.init(EmulatorType.VGZ);
				gameMusicEmu.load("Phantasy Star - Battle.vgz");
			});
			vgzButton.visible = true;
			
			var openButton:PushButton;
			openButton = new PushButton(this, 10, 320 - 90, "Open SPC file...", function (e:Event):void 
			{
				var fileReference:FileReference;
				fileReference = new FileReference();
				
				fileReference.addEventListener(Event.SELECT, function (e:Event):void 
				{
					trace(fileReference.name);
					fileReference.load();
				});
				
				fileReference.addEventListener(Event.COMPLETE, function (e:Event):void 
				{
					if ( gameMusicEmu.isPlaying ) {
						gameMusicEmu.stop();
					}
					gameMusicEmu.init(EmulatorType.SPC);
					gameMusicEmu.loadData(fileReference.data);
				});
				
				// open file choose dialog
				var fileFilter:FileFilter = new FileFilter("SPC File (spc)", "*.spc");
				fileReference.browse([fileFilter]);
			});
			openButton.visible = true;
			
			var pauseButton:PushButton;
			pauseButton = new PushButton(this, 10, 320 - 60, "Pause", function (e:Event):void 
			{
				if ( gameMusicEmu.isPaused ) {
					gameMusicEmu.play();
					return;
				}
				if ( gameMusicEmu.isPlaying ) {
					gameMusicEmu.pause();
					return;
				}
			});
			pauseButton.visible = true;
			
			var stopButton:PushButton;
			stopButton = new PushButton(this, 10, 320 - 30, "Stop", function (e:Event):void 
			{
				if ( gameMusicEmu.isPlaying ) {
					gameMusicEmu.stop();
				}
			});
			stopButton.visible = true;
			
			// create label
			labelInfo = new Label(this, 130, 5, "");
			labelPosition = new Label(this, 210, 280, "");
			labelLength = new Label(this, 250, 280, "");
			
			// create slider
			new Label(this, 130, 200, "Volume");
			var sliderVolume:HSlider = new HSlider(this, 130, 220, function (e:Event):void 
			{
				gameMusicEmu.volume = sliderVolume.value;
			});
			sliderVolume.value = 1.0;
			sliderVolume.maximum = 1.0;
			sliderVolume.width = 170;
			
			new Label(this, 130, 240, "Pan");
			var sliderPan:HSlider = new HSlider(this, 130, 260, function (e:Event):void 
			{
				gameMusicEmu.pan = sliderPan.value;
			});
			sliderPan.value = 0.0;
			sliderPan.minimum = -1.0;
			sliderPan.maximum = 1.0;
			sliderPan.width = 170;
			
			new Label(this, 130, 280, "Position");
			sliderPosition = new HSlider(this, 130, 300, function (e:Event):void 
			{
				if (gameMusicEmu.emulatorType == "") {
					return;
				}
				sliderSeeking = true;
				labelPosition.text = Math.floor(sliderPosition.value).toString();
			});
			stage.addEventListener(MouseEvent.MOUSE_UP, function (e:MouseEvent):void 
			{
				if (sliderSeeking == false) {
					return;
				}
				
				sliderSeeking = false;
				
				if (gameMusicEmu.isPlaying == false) {
					return;
				}
				
				var position:uint = uint(labelPosition.text);
				gameMusicEmu.pause();
				gameMusicEmu.seek(position);
				gameMusicEmu.play();
			});
			sliderPosition.width = 170;
			
			checkSpectrum = new CheckBox(this, 130, 180, "Enable Spectrum Analyzer");
			
			// init GameMusicEmu
			gameMusicEmu = new GameMusicEmu(SampleRate.HIGH);
			gameMusicEmu.addEventListener(Event.COMPLETE, onLoadComplete);
			
			addEventListener(Event.ENTER_FRAME, onEnterFrame);
		}
		
		private function onEnterFrame(e:Event):void 
		{
			if (gameMusicEmu.isPlaying == false) {
				return;
			}
			
			if (checkSpectrum.selected == false) {
				return;
			}
			
			count++;
			
			if (count & 4 == 0) {
				return;
			}
			count = 0;
			
			var sprite:Sprite = new Sprite();
			var g:Graphics = sprite.graphics;
			
			// 周波数帯域ごとのデータを格納する ByteArray の準備
			// 512 個のデータが入る。
			var byteArray:ByteArray = new ByteArray();
			
			// 周波数帯域ごとのデータを取得
			try {
				SoundMixer.computeSpectrum(byteArray, false, 2);
			} catch (e:Error) {
				return;
			}
			byteArray.position = 0;
			
			// 図形をいったんクリア
			g.clear();
			
			// 描く線の状態を初期化
			g.lineStyle(1, 0xFF0000, 0.5);
			
			// 変数の準備
			var i:uint = 0;
			var n:Number = 0;
			
			// 左チャネルのデータを描く
			g.beginFill(0xFF8000);
			g.moveTo(0, 30);
			for (i = 0; i < 32; i++)
			{
				n = 30 - byteArray.readFloat() * 40;
				byteArray.position += 28;
				g.lineTo(i * 4, n);
			}
			g.lineTo(128, 30);
			g.endFill();
			
			// 右チャネルのデータを描く
			g.beginFill(0xFF8000);
			g.moveTo(0, 80);
			byteArray.position = 256 * 4;
			for (i = 0; i < 32; i++)
			{
				n = 80 - byteArray.readFloat() * 40;
				byteArray.position += 28;
				g.lineTo(i * 4, n);
			}
			g.lineTo(128, 80);
			g.endFill();
			
			var data:BitmapData = bitmap.bitmapData;
			data.lock();
			data.fillRect(new Rectangle(0, 0, 128, 112), 0);
			data.draw(sprite);
			data.unlock();
		}
		
		/**
		 * GameMusicEmu load complete event.
		 * @param	e
		 */
		private function onLoadComplete(e:Event):void 
		{
			var info:Object;
			
			// set track number 4, if emulator type is HES
			if (gameMusicEmu.emulatorType == EmulatorType.HES) {
				gameMusicEmu.startTrack(4);
				info = gameMusicEmu.trackInfo(4);
			}
			
			// set track number 43, if emulator type is KSS
			else if (gameMusicEmu.emulatorType == EmulatorType.KSS) {
				gameMusicEmu.startTrack(43);
				info = gameMusicEmu.trackInfo(43);
			}
			
			else {
				// get meta data.
				// it contains "song name", "author", "system" etc..
				info = gameMusicEmu.trackInfo(0);
			}
			
			// get track count.
			trace("track count: " + gameMusicEmu.trackCount());
			
			// set volume
			//gameMusicEmu.volume = 0.1;
			
			// seek player position. 1000 = 1 sec.
			//gameMusicEmu.seek(10000);
			
			// set stereo surround
			//gameMusicEmu.setStereoDepth(1.0);
			
			// set fade out
			//gameMusicEmu.setFade(1000);
			
			// start player
			gameMusicEmu.play();
			
			
			var str:String;
			str = "[System] " + info.system + "\n";
			str += "[Game] " + info.game + "\n";
			str += "[Song] " + info.song + "\n";
			str += "[Copyright] " + info.copyright + "\n";
			str += "[Play length] " + info.play_length + "\n";
			
			// show meta data
			labelInfo.text = str;
			
			// set label
			labelPosition.text = "0";
			labelLength.text = "/ " + info.play_length;
			
			// set slider position
			sliderPosition.value = 0;
			sliderPosition.maximum = info.play_length;
			
			// init timer
			if (timer != null) {
				timer.stop();
			}
			timer = new Timer(100, 0);
			timer.addEventListener(TimerEvent.TIMER, function ():void 
			{
				if (sliderSeeking) {
					return;
				}
				// get player's current position. 1000 = 1 sec.
				var position:uint = gameMusicEmu.tell();
				sliderPosition.value = position;
				labelPosition.text = position.toString();
				// true, if music is ended.
				//trace("ended: " + gameMusicEmu.trackEnded());
			});
			timer.start();
		}
		
	}
	
}