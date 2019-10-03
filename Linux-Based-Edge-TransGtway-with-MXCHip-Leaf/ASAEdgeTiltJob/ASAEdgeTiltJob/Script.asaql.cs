using System;

namespace ASAEdgeTiltJob
{
    public class Trigonometry
    {
        public static double CalculateTilt(double pitch, double roll)
        {
            var pitchRads = DegreesToRadians(pitch);
            var rollRads = DegreesToRadians(roll);
            var tiltRads = Math.Acos(Math.Cos(pitchRads) * Math.Cos(rollRads));
            return RadiansToDegrees(tiltRads);
        }

        private static double DegreesToRadians(double degrees)
        {
            return degrees * Math.PI / 180;
        }

        private static double RadiansToDegrees(double radians)
        {
            return radians * 180 / Math.PI;
        }
    }
}
