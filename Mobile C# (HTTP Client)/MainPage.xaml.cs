using System;
using System.Net.Http;
using Xamarin.Forms;
using System.Net;
using System.Threading;

namespace HTTPsvetoforSender
{
	public partial class MainPage : ContentPage
	{
		public MainPage()
		{
            InitializeComponent();
		}

		//Request (Event) handler
		//
        private async void Green_wave_ClickedAsync(object sender, EventArgs e)
        {
            Green_wave.BackgroundColor = Color.Red;	//Inform user about inability to press the button
            Green_wave.IsEnabled = false; 			//The button really set to inability press mode
            GreenLabel.IsVisible = false; 			//The inform label is erased from display
            RedLabel.IsVisible   = true;		    //The warning label is shown on display		
            
            string request = "http://192.168.1.1/?t=1"; //Create the request by rule (IP and argument)	

            var uri = new Uri(request); 				//Create the Uniform Resource Identifier
	
            HttpClient Client = new HttpClient();  	    //Create the HTTP instance

            while (true) 								
            {
                var response = await Client.PostAsync(uri, null); //Asynchronous polling the server  

                if (response.StatusCode == HttpStatusCode.OK)     //If connection has been established
                {
                    RedLabel.IsVisible   = false;			  //The warning label is erased from display				
                    GreenLabel.IsVisible = true; 			  //The inform label is shown on display
                    Green_wave.IsEnabled = true;			  //The button set to the pressing ability mode 
                    Green_wave.BackgroundColor = Color.Green; //Inform user about the ability to press the button 
                    break; 
                }

                Thread.Sleep(10000); //Polling server each ten seconds  
            }
        }
    }
}
