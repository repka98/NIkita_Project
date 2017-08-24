var X_AXIS = 0;
var Y_AXIS = 1;
var Z_AXIS = 2;

Scene = function ( parameters ) {

	this.scene;
	this.render;
	this.camera;

	this.controls = false;
	this.orbitControls;

	this.displayStats = false;
	this.stats;

	this.ambientLight;
	this.diretionalLight;

	this.axisHeight = 0;

	this.setParametrs( parameters );
};

Scene.prototype = {
	setParametrs: function( values ) {
		if (values === undefined ) return;

		for ( var key in values ) {
			var newValue = values[ key ];

			if ( newValue === undefined ) {
				console.warn("NEHE: " + key + " parameter is undefined");
				continue;
			}

			if ( key in this ) {
				var currentValue = this[ key ];

				if ( currentValue instanceof THREE.Color ) {
					currentValue.set( newValue );
				}else if (currentValue instanceof THREE.Vector3 && newValue instanceof THREE.Vector3) {
					currentValue.copy( newValue );
				}else if ( key == 'overdraw' ) {
					this[ key ] = Number( newValue );
				}else {
					this[ key ] = newValue;
				}
			}
		} 
	},

	initialize: function() {
		if ( !Detector.webgl ) {
			Detector.addGetWebGLMessage();
		}

		this.scene = new THREE.Scene();

		var canvasWidth = window.innerWidth;
		var canvasHeight = window.innerHeight;

		var container;
		var containerID;
		if ( containerID != null && typeof containerID != 'undefined')
			container = document.getElementByTd(containerID);

		if (container == null || typeof container == 'undefined') {
			container = document.createElement('div');
			document.body.appendChild( container );
		}else {
			canvasWidth = container.clientWidth;
			canvasHeight = container.clientHeight;
		}

		this.camera = new THREE.PerspectiveCamera(45, canvasWidth / canvasHeight, 0.1, 1000);
		this.camera.position.set(0, 6, 6);
		this.camera.lookAt(this.scene.position);
		this.scene.add(this.camera);

		this.renderer = new THREE.WebGLRenderer({ antialias: true });

		this.renderer.setClearColor(0x000000, 1);

		this.renderer.setSize(canvasWidth, canvasHeight);

		container.appendChild(this.renderer.domElement);

		this.ambientLight = new THREE.AmbientLight(0x404040);
		this.scene.add(this.ambientLight);

		this.directionalLight = new THREE.PointLight(0xffffff);
		this.directionalLight.position.set(250, 250, 250);
		this.scene.add(this.directionalLight);


		if ( this.controls == true) {
			this.orbitControls = new THREE.OrbitControls(this.camera, this.renderer.domElement);
		}

		if (this.axisHeight != 0 ) {
			this.drawAxes( this.axisHeight );
		}


		if ( this.displayStats == true ) {
			this.stats = new Stats(); 
			this.stats.domElement.style.position = 'absolute';
			this.stats.domElement.style.bottom = '0px';
			this.stats.domElement.style.zIndex = 100;
			container.appendChild( this.stats.domElement);
		}
	},

	addToScene: function ( obj ) {
		this.scene.add( obj );
	},


	renderScene: function () {
		this.renderer.render(this.scene, this.camera);

		if (this.orbitControls != null && typeof this.orbitControls != 'undefined')
			this.orbitControls.update();

		if (this.stats != null && typeof this.stats != 'undefined')
			this.stats.update();
	},


	drawAxis: function (axis, axisColor, axisHeight ) {
		var AXIS_RADIUS = axisHeight / 200.0;
		var AXIS_HEIGHT = axisHeight;
		var AXIS_STEP = axisHeight / 20.0;
		var AXIS_SEGMENTS = 32;
		var AXIS_GREY = 0x777777;
		var AXIS_WHITE = 0xEEEEEE;

		for ( i = 0; i < (AXIS_HEIGHT / AXIS_STEP); i++) {
			var pos = -AXIS_HEIGHT / 2 + i * AXIS_STEP;

			if ((i & 1) == 0) {
				curColor = axisColor;
			}else if ( pos < 0) {
				curColor = AXIS_GREY;
			}else {curColor = AXIS_WHITE;}

			var geometry = new THREE.CylinderGeometry( AXIS_RADIUS, AXIS_RADIUS, AXIS_STEP, AXIS_SEGMENTS);
			var material = new THREE.MeshLambertMaterial({ color: curColor});
			var cylinder = new THREE.Mesh( geometry, material );

			pos += AXIS_STEP / 2.0;
			if (axis == X_AXIS) {
				cylinder.position.x = pos;
				cylinder.rotation.z = Math.PI / 2;
			}else if (axis == Y_AXIS) {
				cylinder.rotation.y = Math.PI / 2;
				cylinder.position.y = pos;
			}else {
				cylinder.position.z = pos;
				cylinder.rotation.x = math.PI / 2;
			}

			this.scene.add( cylinder );
		};
	},

	drawAxes: function( height ) {
		this.drawAxis(X_AXIS, 0xff0000, height);
		this.drawAxis(X_AXIS, 0x00ff00, height);
		this.drawAxis(X_AXIS, 0x0000ff, height);
	}
}