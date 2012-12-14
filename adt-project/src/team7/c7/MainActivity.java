package team7.c7;

import team7.c7.R;
import android.os.Bundle;
import android.app.Activity;
import android.view.Menu;
import android.widget.ImageButton;
import java.util.Arrays;
import android.os.Bundle;
import android.app.Activity;
import android.view.Menu;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.TextView;

import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.content.Context;

	public class MainActivity extends Activity {
		   SensorManager mSensorManager;
		int count,i,k;

		int c1,c2,c3,c4,c5,c6,c7,isAI=0;
		int[][] btns = {{R.id.ImageButton11,R.id.ImageButton12,R.id.ImageButton13,R.id.ImageButton14,R.id.ImageButton15,R.id.ImageButton16},
		 				{R.id.ImageButton21,R.id.ImageButton22,R.id.ImageButton23,R.id.ImageButton24,R.id.ImageButton25,R.id.ImageButton26},
		 				{R.id.ImageButton31,R.id.ImageButton32,R.id.ImageButton33,R.id.ImageButton34,R.id.ImageButton35,R.id.ImageButton36},
		 				{R.id.ImageButton41,R.id.ImageButton42,R.id.ImageButton43,R.id.ImageButton44,R.id.ImageButton45,R.id.ImageButton46},
		 				{R.id.ImageButton51,R.id.ImageButton52,R.id.ImageButton53,R.id.ImageButton54,R.id.ImageButton55,R.id.ImageButton56},
		 				{R.id.ImageButton61,R.id.ImageButton62,R.id.ImageButton63,R.id.ImageButton64,R.id.ImageButton65,R.id.ImageButton66},
		 				{R.id.ImageButton71,R.id.ImageButton72,R.id.ImageButton73,R.id.ImageButton74,R.id.ImageButton75,R.id.ImageButton76}};
		//initiate a two dimensional matrix of name tags for each white circle, so we can change their color later by referencing their row and column
		
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);		
	    
		/* do this in onCreate */
	    mSensorManager = (SensorManager) getSystemService(Context.SENSOR_SERVICE);
	    
	    mSensorManager.registerListener(mSensorListener, mSensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER), SensorManager.SENSOR_DELAY_NORMAL);
	    mAccel = 0.00f;
	    mAccelCurrent = SensorManager.GRAVITY_EARTH;
	    mAccelLast = SensorManager.GRAVITY_EARTH;

		setContentView(R.layout.activity_start_screen);	
		initStart();	
	}
	
	
	
	public void initStart(){ //initiate the start screen buttons
		c1=c2=c3=c4=c5=c6=c7=0;
		count=0;
		Button bt;
		gameReset();
		bt = (Button) this.findViewById(R.id.SinglePlayer);
		bt.setOnClickListener(slistener);
		bt = (Button) this.findViewById(R.id.TwoPlayer);
		bt.setOnClickListener(slistener);
		bt = (Button) this.findViewById(R.id.exit1);
		bt.setOnClickListener(slistener);
    }

	
	
	public OnClickListener slistener = new OnClickListener() { //conditions when start screen buttons are clicked
        public void onClick(View v) {
        	switch(v.getId()){	
        	case R.id.SinglePlayer:  
        		setContentView(R.layout.main);		//change to main game board
        		init();								//initiate the game play button layout
        		setupGame(1);						//setup the game back end as AI vs Human
        		isAI = 1;							//setup front end for AI vs human mode
        		break;
        	case R.id.TwoPlayer:	
        		setContentView(R.layout.main);		//change to main game board
        		init();								//initiate the game play button layout
        		isAI=0;								//setup front end for Human vs Human mode
        		setupGame(0);     					//setup the game back end as Human vs Human
        		i=k=0;							
        		break;
        	case R.id.exit1:
        		close();
        		break;
        	}
        }
	};
	
	
	
	
	public void init(){								//initiate the game play screen buttons
		c1=c2=c3=c4=c5=c6=c7=k=0;					//initiate variables that count placed marker for each row  
		ImageButton IMB;							
		Button BT;
		count=0;
		gameReset();								//initiate the back end of the game
		
		IMB = (ImageButton) this.findViewById(R.id.ImageButton01);//initiate buttons with listener
    	IMB.setOnClickListener(listener);
    	IMB = (ImageButton) this.findViewById(R.id.ImageButton02);
    	IMB.setOnClickListener(listener);
    	IMB = (ImageButton) this.findViewById(R.id.ImageButton03);
    	IMB.setOnClickListener(listener);
    	IMB = (ImageButton) this.findViewById(R.id.ImageButton04);
    	IMB.setOnClickListener(listener);
    	IMB = (ImageButton) this.findViewById(R.id.ImageButton05);
    	IMB.setOnClickListener(listener);
    	IMB = (ImageButton) this.findViewById(R.id.ImageButton06);
    	IMB.setOnClickListener(listener);
    	IMB = (ImageButton) this.findViewById(R.id.ImageButton07);
    	IMB.setOnClickListener(listener);
    	
    	BT = (Button) this.findViewById(R.id.Reset);			
    	BT.setOnClickListener(listener);
    	BT = (Button) this.findViewById(R.id.Exit);
    	BT.setOnClickListener(listener);   
	}
	
	
	
	public OnClickListener listener = new OnClickListener() {
		public void onClick(View v) {				//conditions when game play screen buttons are clicked
			ImageButton C_button;
			TextView TV;
			Button button;
			switch (v.getId()) {					//if the current button id is match match with the id below
			case R.id.ImageButton01:
				i = 0;								//giving numerical tags for the button
				c1++;								//each time the column button is clicked, the row mark up once
				k = c1;								
				break;
			case R.id.ImageButton02:
				i = 1;
				c2++;
				k = c2;
				break;
			case R.id.ImageButton03:
				i = 2;
				c3++;
				k = c3;
				break;
			case R.id.ImageButton04:
				i = 3;
				c4++;
				k = c4;
				break;
			case R.id.ImageButton05:
				i = 4;
				c5++;
				k = c5;
				break;
			case R.id.ImageButton06:
				i = 5;
				c6++;
				k = c6;
				break;
			case R.id.ImageButton07:
				i = 6;
				c7++;
				k = c7;
				break;
			case R.id.Exit:							//when exit button is clicked
				count = 47;							//make count large enough so the program escape to restart directly
				k = 8;
				setContentView(R.layout.activity_start_screen); //change to start screen
				initStart();									//initiate start screen buttons
				break;
			case R.id.Reset:						//when reset button is clicked
				count = -2;							//set count to-2 to restart
				k = 8;								
				break;
			}
			k--;
			
			if (count == -2) {						//if count is -2 restart the game
				restart();
			}
			else if (count != -1) {
				System.out.println(makeGameMove(i)); //pass the column that's been clicked to back end

				if (getGameState() == 2) {
					TV = (TextView) findViewById(R.id.game_name);// change the
																	// string to
																	// notify
																	// player
																	// (who's
																	// turn)
					TV.setText(R.string.P2_won);
					winning(0);
					count = -1;
					k = 8;
				} else if (getGameState() == 1) {
					TV = (TextView) findViewById(R.id.game_name);// change the
																	// string to
																	// notify
																	// player
																	// (who's
					winning(1);								// turn)
					TV.setText(R.string.P1_won);
					count = -1;
					k = 8;
				} else if (getGameState() == -1) {
					TV = (TextView) findViewById(R.id.game_name);// change the
																	// string to
																	// notify
																	// player
																	// (who's
																	// turn)
					TV.setText(R.string.draw);
					count = -1;
					k = 8;
				}
				int kAI = 0;										
				if (k < 6) {
					if (isAI == 1) {								//when 1 player is selected, AI mode is on
						System.out.println(getLastMove());

						int j = makeGameMove(-1);					//j is the column the AI will be move after calculation
						System.out.println(getLastMove());
						switch (j) {								
						case 0:										//when j is the first column, add one board piece to the row 
							c1++;
							kAI = c1;								//assign the row that will be displayed based on the number of piece is already in the column
							break;
						case 1:
							c2++;
							kAI = c2;
							break;
						case 2:
							c3++;
							kAI = c3;
							break;
						case 3:
							c4++;
							kAI = c4;
							break;
						case 4:
							c5++;
							kAI = c5;
							break;
						case 5:
							c6++;
							kAI = c6;
							break;
						case 6:
							c7++;
							kAI = c7;
							break;
						}
						kAI--;	
						
						
						
						
						TV = (TextView) findViewById(R.id.Move);// change the
																// string to
																// notify player
																// (who's turn)
						TV.setText(R.string.Player1);
						
						C_button = (ImageButton) findViewById(btns[i][k]);//change the color of the button that Human played to red
						C_button.setImageResource(R.drawable.reds);

						
						count++;

						
						C_button = (ImageButton) findViewById(btns[j][kAI]);//change the color of the button that AI played to blue
						C_button.setImageResource(R.drawable.blues);

						
						count++;

						
						
						if (getGameState() == 2) {
							TV = (TextView) findViewById(R.id.game_name);// change the
																			// string to
																			// notify
																			// player
																			// (who's
																			// win)
							winning(0);										
							TV.setText(R.string.P2_won);
							count = -1;										//when won, restart
							k = 8;
						} else if (getGameState() == 1) {
							TV = (TextView) findViewById(R.id.game_name);// change the
																			// string to
																			// notify
																			// player
																			// (who's
																			// win)
							winning(1);										
							TV.setText(R.string.P1_won);
							count = -1;
							k = 8;
						} else if (getGameState() == -1) {
							TV = (TextView) findViewById(R.id.game_name);// change the
																			// string to
																			// notify
																			// player
																			// (who's
																			// win)
							TV.setText(R.string.draw);
							count = -1;
							k = 8;
							
							
						}
						
					} 
					else {
						if (count % 2 == 0) {								//if the turn is even, it's player one's turn
							C_button = (ImageButton) findViewById(btns[i][k]);
							C_button.setImageResource(R.drawable.reds);
							TV = (TextView) findViewById(R.id.Move);// change
																	// the
																	// string to
																	// notify
																	// player
																	// (who's
																	// turn)
							TV.setText(R.string.Player2);
							count++;
						} else {
							C_button = (ImageButton) findViewById(btns[i][k]);
							C_button.setImageResource(R.drawable.blues);
							TV = (TextView) findViewById(R.id.Move); // change
																		// the
																		// string
																		// to
																		// notify
																		// player
																		// (who's
																		// turn)
							TV.setText(R.string.Player1);

							count++;
						}
					}
					if (getGameState() == 2) {

						TV = (TextView) findViewById(R.id.game_name);// change the
																	// string to
																	// notify
																	// player
																	// (who's
																	// turn)
						winning(0);										
						TV.setText(R.string.P2_won);

						count=-1; k=8;
					} else if (getGameState() == 1) {
						TV = (TextView) findViewById(R.id.game_name);// change the
																	// string to
																	// notify
																	// player
																	// (who's
																	// turn)
						winning(1);									
						TV.setText(R.string.P1_won);
						;
						count=-1; k=8;
					} else if (getGameState() == -1) {
						TV = (TextView) findViewById(R.id.game_name);// change the
																	// string to
																	// notify
																	// player
																	// (who's
																	// turn)
						TV.setText(R.string.draw);

						count=-1; k=8;
					}
					System.out.println(count);
				} else if (count > 42) {
					
					restart();
				}
			}
		}
	};
    
    public void close(){											//when exit button on the start screen is pressed, close the application windows
    	finish();
    }
    public void restart(){											//restart the game by reset the layout and buttons
    	setContentView(R.layout.main);
        init();
    } 
    
    
	@Override
	public boolean onCreateOptionsMenu(Menu menu) {					
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

	/* put this into your activity class */

	  private float mAccel; // acceleration apart from gravity
	  private float mAccelCurrent; // current acceleration including gravity
	  private float mAccelLast; // last acceleration including gravity
	  private float THRESHOLD = 8.75f;
	 
	  private final SensorEventListener mSensorListener = new SensorEventListener() {

	    public void onSensorChanged(SensorEvent se) {
	      float x = se.values[0];
	      float y = se.values[1];
	      float z = se.values[2];
	      mAccelLast = mAccelCurrent;
	      mAccelCurrent = (float) Math.sqrt((double) (x*x + y*y + z*z));
	      float delta = mAccelCurrent - mAccelLast;
	      mAccel = mAccel * 0.9f + delta; // perform low-cut filter
	      System.out.println(mAccel);	
	      if (mAccel > THRESHOLD)
	    	  restart();		//restart the game when it's been shaked
	    }

	    public void onAccuracyChanged(Sensor sensor, int accuracy) {
	    }
	  };

	  @Override
	  protected void onResume() {
	    super.onResume();
	    mSensorManager.registerListener(mSensorListener, mSensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER), SensorManager.SENSOR_DELAY_NORMAL);
	  }
	  
	

	public void winning(int color) {  // color all the dots the on winning
		ImageButton C_button;
		for (int t=0;t<7;t++) {
			for (int f=0;f<6;f++){ 
				C_button = (ImageButton) findViewById(btns[t][f]);
				if (color==0)
					C_button.setImageResource(R.drawable.blues);
				else
					C_button.setImageResource(R.drawable.reds);
			}
		}
	}
	
	
	public native void gameReset(); //reset game back end 

	// Get game state from C++ backend
	// -1 Draw
	// 0 Nothing Special
	// 1 Player 1 Won
	// 2 Player 2 Won
	public native int getGameState();


	
	
	// Pass ai as 1 if need to setup ai
	// Pass ai as 0 if second player is human
	public native void setupGame(int ai);



	
	// Returns 1 if current player is AI
	// Returns 0 if current player is Human
	public native int isCurrentAI();
	
	
	
	
	// Pass move return -1 if invalid move was made.
	// Move can be anything (preferably -1) for AI player.
	public native int makeGameMove(int move);
	
	
	
	
	// Returns current player (0 for player 1, 1 for player 2)
	public native int getCurrentPlayer();
	
	
	
	// Returns the column of the last move made (use for populatibng columns)
	public native int getLastMove();
	
	
	
	static {
		System.loadLibrary("C4");
	}
	
	
	
	
}
	
	
