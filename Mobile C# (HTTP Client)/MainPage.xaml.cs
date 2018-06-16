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


        private async void Green_wave_ClickedAsync(object sender, EventArgs e)
        {
            Green_wave.BackgroundColor = Color.Red;  
            Green_wave.IsEnabled = false; 
            GreenLabel.IsVisible = false; 
            RedLabel.IsVisible = true;
            
            
            string request =
                "http://192.168.1.1/?t=1"; 

            var uri = new Uri(request); 

            HttpClient Client = new HttpClient();  

            while (true) 
            {
                var response = await Client.PostAsync(uri, null); 

                if (response.StatusCode == HttpStatusCode.OK) 
                {
                    RedLabel.IsVisible = false; 
                    GreenLabel.IsVisible = true; 
                    Green_wave.IsEnabled = true; 
                    Green_wave.BackgroundColor = Color.Green; 
                    break; 
                }

                Thread.Sleep(300); 
            }
        }
    }
}
