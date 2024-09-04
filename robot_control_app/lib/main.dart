import 'package:flutter/material.dart';
import 'package:http/http.dart' as http;
import 'dart:async';

void main() {
  runApp(MyApp());
}

class MyApp extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Robot Control Center',
      theme: ThemeData(
        primarySwatch: Colors.blue,
        visualDensity: VisualDensity.adaptivePlatformDensity,
      ),
      home: HomeScreen(),
    );
  }
}

class HomeScreen extends StatefulWidget {
  final String ipAddress = '192.168.79.133';  // Ensure this matches your actual ESP8266 IP address

  HomeScreen({Key? key}) : super(key: key);

  @override
  _HomeScreenState createState() => _HomeScreenState();
}

class _HomeScreenState extends State<HomeScreen> {
  Timer? _timer;

  void sendCommand(String command) async {
    try {
      final url = Uri.http(widget.ipAddress, command);
      final response = await http.get(url);
      if (response.statusCode != 200) {
        throw Exception('Failed to send command');
      }
      print("Command sent: $command"); // Debugging output
    } catch (e) {
      print("Failed to connect to the device: $e");
    }
  }

  Widget directionalButton(IconData icon, String command) {
    return Listener(
      onPointerDown: (_) => sendCommand(command),
      onPointerUp: (_) => sendCommand('stop'),
      child: ElevatedButton(
        onPressed: () {},  // This keeps the button visually responsive
        style: ElevatedButton.styleFrom(
          backgroundColor: Colors.blue,
          shape: CircleBorder(),
          padding: EdgeInsets.all(24),
        ),
        child: Icon(icon, color: Colors.white),
      ),
    );
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('Robot Control Center'),
      ),
      body: Center(
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: <Widget>[
            directionalButton(Icons.arrow_upward, 'forward'),
            SizedBox(height: 20),
            Row(
              mainAxisAlignment: MainAxisAlignment.center,
              children: [
                directionalButton(Icons.arrow_back, 'left'),
                SizedBox(width: 50), // Space between left and right buttons
                directionalButton(Icons.arrow_forward, 'right'),
              ],
            ),
            SizedBox(height: 20),
            directionalButton(Icons.arrow_downward, 'back'),
            SizedBox(height: 20),
            ElevatedButton(
              onPressed: () => sendCommand('stop'),
              child: Text('Stop'),
              style: ElevatedButton.styleFrom(
                backgroundColor: Colors.black,
                padding: EdgeInsets.symmetric(horizontal: 50, vertical: 20),
              ),
            ),
            SizedBox(height: 20),
            ElevatedButton(
              onPressed: () => sendCommand('auto/on'),
              child: Text('Enable Autonomous Mode'),
              style: ElevatedButton.styleFrom(
                backgroundColor: Colors.purple,
                padding: EdgeInsets.symmetric(horizontal: 20, vertical: 20),
              ),
            ),
            SizedBox(height: 10),
            ElevatedButton(
              onPressed: () => sendCommand('auto/off'),
              child: Text('Disable Autonomous Mode'),
              style: ElevatedButton.styleFrom(
                backgroundColor: Colors.grey,
                padding: EdgeInsets.symmetric(horizontal: 20, vertical: 20),
              ),
            ),
          ],
        ),
      ),
    );
  }
}
